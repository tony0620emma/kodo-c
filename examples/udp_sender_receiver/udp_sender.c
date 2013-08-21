// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <stdint.h>
#include <ckodo/ckodo.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* memset() */
#include <sys/time.h> /* select() */
#include <time.h>
#include <sys/timeb.h>
#include <assert.h>



int main(int argc, char *argv[])
{

    // Variables needed for the network / socket usage
    int32_t socket_descriptor;
    int32_t return_code;
    int32_t i;

    struct sockaddr_in local_address;
    struct sockaddr_in remote_address;
    struct hostent *host;

    struct timespec delay; // Delay between packets
    struct timeb start_time;
    struct timeb end_time;

    // Variables needed for the coding
    uint32_t max_symbols = 32;
    uint32_t max_symbol_size = 160;

    uint32_t symbols = 0;
    uint32_t symbols_size = 0;

    size_t algorithm = kodo_on_the_fly;
    size_t finite_field = kodo_binary8;

    kodo_factory_t* encoder_factory = 0;
    kodo_coder_t* encoder = 0;

    // The buffer sent to the receiver
    uint32_t payload_size = 0;
    uint8_t* payload = 0;

    // The data to be encoded
    uint32_t block_size = 0;
    uint8_t* data_in = 0;

    // Check command line args
    if(argc < 4)
    {
        printf("usage : %s <server> <port> <num_packets> <delay_pico_sec>\n",
               argv[0]);

        exit(1);
    }

    if (argc == 4)
    {
        delay.tv_sec  = 0;
        delay.tv_nsec = 0;
    }
    else
    {
        delay.tv_sec  = atol(argv[4]) / 1000000;
        delay.tv_nsec = (atol(argv[4]) % 1000000)*1000;
    }

    printf("Delay is %ld ns\n", delay.tv_nsec);

    // Get server IP address (no check if input is IP address or DNS name)
    host = gethostbyname(argv[1]);
    if(host == NULL)
    {
        printf("%s: unknown host '%s' \n", argv[0], argv[1]);
        exit(1);
    }

    printf("Sending data to '%s:%d' (IP: %s) \n", host->h_name,
           atoi(argv[2]), inet_ntoa(*(struct in_addr *)host->h_addr_list[0]));

    remote_address.sin_family = host->h_addrtype;
    memcpy((char *) &remote_address.sin_addr.s_addr,
           host->h_addr_list[0], host->h_length);
    remote_address.sin_port = htons(atoi(argv[2]));

    // Socket creation
    socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_descriptor < 0)
    {
        printf("%s: cannot open socket \n",argv[0]);
        exit(1);
    }

    // Bind any port
    local_address.sin_family = AF_INET;
    local_address.sin_addr.s_addr = htonl(INADDR_ANY);
    local_address.sin_port = htons(0);

    return_code = bind(socket_descriptor, (struct sockaddr *) &local_address,
                       sizeof(local_address));

    if(return_code < 0)
    {
        printf("%s: cannot bind port\n", argv[0]);
        exit(1);
    }

    // Create the encoder factory
    encoder_factory = kodo_new_encoder_factory(
        algorithm, finite_field, max_symbols, max_symbol_size);

    // Initialize the factory with the chose symbols and symbol size
    symbols = atoi(argv[3]);
    assert(symbols < max_symbols);

    kodo_factory_set_symbols(encoder_factory, symbols);
    encoder = kodo_factory_new_encoder(encoder_factory);

    // Create the buffer needed for the payload
    payload_size = kodo_payload_size(encoder);
    payload = (uint8_t*)malloc(payload_size);

    // Create some data to encode
    block_size = kodo_block_size(encoder);
    data_in = (uint8_t*)malloc(block_size);

    for (i = 0; i < block_size; ++i)
        data_in[i] = rand() % 256;

    // Send data
    ftime(&start_time);
    for(i = 0; i < symbols; ++i)
    {
        if (kodo_rank(encoder) < kodo_symbols(encoder))
        {
            // The rank of an encoder indicates how many symbols have
            // been added, i.e. how many symbols are available for encoding
            uint32_t rank = kodo_rank(encoder);

            // Calculate the offset to the next symbol to insert
            uint8_t* symbol = data_in + (rank * kodo_symbol_size(encoder));
            kodo_set_symbol(encoder, rank, symbol, kodo_symbol_size(encoder));
        }


        uint32_t bytes_used = kodo_encode(encoder, payload);
        printf("Payload generated by encoder, rank = %d, bytes used = %d\n",
               kodo_rank(encoder), bytes_used);

        return_code = sendto(socket_descriptor, payload, bytes_used, 0,
                    (struct sockaddr *) &remote_address,
                    sizeof(remote_address));

        if(return_code<0)
        {
            printf("%s: cannot send data %d \n",argv[0],i-1);
            close(socket_descriptor);
            exit(1);
        }

        nanosleep(&delay, NULL);
    }
    ftime(&end_time);

    printf("Time needed: %ld ms\n",
           (end_time.time*1000+end_time.millitm)-(start_time.time*1000+start_time.millitm));

    return 1;
}


