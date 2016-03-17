#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <kodoc/kodoc.h>

void error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void trace_callback(const char* zone, const char* data, void* context)
{
	(void) context;

	if (strcmp(zone, "decoder_state") == 0) {
		printf("%s:\n", zone);
		printf("%s\n", data);
	}
}

static double diff_in_second(struct timespec t1, struct timespec t2)
{
	struct timespec diff;
	if (t2.tv_nsec-t1.tv_nsec < 0) {
		diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
	} else {
		diff.tv_sec  = t2.tv_sec - t1.tv_sec;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
	}
	return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char* argv[])
{
	struct timespec start, end;
	struct hostent *server;
	double cpu_time;

	uint32_t max_symbols = 10;
	uint32_t max_symbol_size = 100;

	int32_t codec = kodoc_full_vector;	
	int32_t finite_field = kodoc_binary;

	kodoc_factory_t decoder_factory =
        kodoc_new_decoder_factory(codec, finite_field,
                                 max_symbols, max_symbol_size);
	kodoc_coder_t decoder = kodoc_factory_build_coder(decoder_factory);

	uint32_t bytes_used;
	uint32_t payload_size = kodoc_payload_size(decoder);
	uint32_t block_size = kodoc_block_size(decoder);	
	uint8_t* payload = (uint8_t*) malloc(payload_size);
	uint8_t* data_out = (uint8_t*) malloc(block_size);

	int sockfd, portno, numbytes, ack, last_size = 0;
	struct sockaddr_in server_addr;
	struct stat filestat;

	if (argc < 4) {
		fprintf(stdout, "Usage: %s host_name host_port file_name\n", argv[0]);
		error("ERROR: invalid argument");
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		error("socket");

	portno = atoi(argv[2]);
	server = gethostbyname(argv[1]);
	if (!server)
		error("ERROR: no such host");

	memset(&server_addr, 0, sizeof(server_addr));
	memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portno);

	if (connect(sockfd, (struct sockaddr*) &server_addr, sizeof(struct sockaddr)) == -1)
		error("connect");

	FILE *fp;
	if ((fp = fopen(argv[3], "w")) == NULL)
		error("fopen");
	
	printf("Opening file: \"%s\"\n", argv[3]);
	clock_gettime(CLOCK_REALTIME, &start);

	/* read file size from server to know how much data remained */
	if (read(sockfd, &filestat.st_size, sizeof(filestat.st_size)) < 0)
		error("Error:read file_size failed");

	printf("The file size is %lu bytes\n", filestat.st_size);
	kodoc_delete_coder(decoder);

	// Decode one block at a time, check decoder is complete or not,
	// return ack to let the server know the decode state,
	// if block is decoded, reset decoder state and write the file,
	// until all the data is received.

	while (filestat.st_size > 0) {
		if (filestat.st_size < block_size)
			last_size = filestat.st_size;

		filestat.st_size -= block_size;
		kodoc_coder_t decoder = kodoc_factory_build_coder(decoder_factory);		
		kodoc_set_mutable_symbols(decoder, data_out, block_size);
		kodoc_set_trace_stdout(decoder);
		kodoc_set_trace_callback(decoder, trace_callback, NULL);

		while (1) {
			if (read(sockfd, payload, payload_size) < 0)
				error("Error:read payload failed");

			kodoc_read_payload(decoder, payload);
			printf("block_size:%d\n", block_size);
			printf("payload_size:%d\n", payload_size);
			printf("Payload processed by decoder, current rank = %d\n\n", kodoc_rank(decoder));

			ack = kodoc_is_complete(decoder);

			/* send ack to let server know that decode is sucessful or not */
			if (write(sockfd, &ack, sizeof(ack)) < 0)
				error("\n Error:write ack failed\n");

			if (ack == 1) {		
				printf("decoded finished\n");

				if (last_size == 0)
					numbytes = fwrite(data_out, sizeof(char), block_size, fp);
				else
					numbytes = fwrite(data_out, sizeof(char), last_size, fp);

				printf("fwrite %d bytes\n\n", numbytes);
				memset(payload, 0, payload_size);
				kodoc_delete_coder(decoder);
				break;
			}
		} /* end of while (1) */
	} /* end of while (filestat.st_size > 0) */

	clock_gettime(CLOCK_REALTIME, &end);
	cpu_time = diff_in_second(start, end);
	printf("execution time of transmission : %lf sec\n", cpu_time);
	printf("client finished\n");

	free(data_out);
	free(payload);
	kodoc_delete_factory(decoder_factory);
	fclose(fp);
	close(sockfd);
	return 0;
}
