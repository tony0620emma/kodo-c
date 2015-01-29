// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <kodoc/kodoc.h>

/// @example sliding_window.c
///
/// This example shows how to use the sliding window encoder and decoder
/// stacks. The sliding window is special in that it does not require
/// that all symbols are available at the encoder before encoding can
/// start. In addition, it uses feedback between the decoder and encoder
/// such that symbols that have already been received at the decoder
/// are not included in the encoding again (saving computations).

void trace_callback(const char* zone, const char* data)
{
    if (strcmp(zone, "decoder_state") == 0 ||
        strcmp(zone, "input_symbol_coefficients") == 0)
    {
        printf("%s:\n", zone);
        printf("%s\n", data);
    }
}

int main()
{
    // Seed random number generator to produce different results every time
    srand(time(NULL));

    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint8_t max_symbols = 6;
    uint8_t max_symbol_size = 160;

    int32_t code_type = kodo_sliding_window;
    int32_t finite_field = kodo_binary8;

    // In the following we will make an encoder/decoder factory.
    // The factories are used to build actual encoders/decoders
    kodo_factory_t encoder_factory =
        kodo_new_encoder_factory(code_type, finite_field,
                                 max_symbols, max_symbol_size,
                                 kodo_trace_disabled);

    kodo_factory_t decoder_factory =
        kodo_new_decoder_factory(code_type, finite_field,
                                 max_symbols, max_symbol_size,
                                 kodo_trace_enabled);

    // If we wanted to build an encoder or decoder with a smaller number of
    // symbols or a different symbol size, then this can be adjusted using the
    // following functions:
    //      kodo_factory_set_symbols(...)
    //      kodo_factory_set_symbol_size(...)
    // We cannot exceed the maximum values which was used when building
    // the factory.
    kodo_coder_t encoder = kodo_factory_new_encoder(encoder_factory);
    kodo_coder_t decoder = kodo_factory_new_decoder(decoder_factory);

    // Allocate some storage for a "payload" the payload is what we would
    // eventually send over a network
    uint32_t payload_size = kodo_payload_size(encoder);
    uint8_t* payload = (uint8_t*) malloc(payload_size);

    // Allocate some data to encode. In this case we make a buffer
    // with the same size as the encoder's block size (the max.
    // amount a single encoder can encode)
    uint32_t block_size = kodo_block_size(encoder);
    uint8_t* data_in = (uint8_t*) malloc(block_size);

    uint8_t feedback_size = (uint8_t) kodo_feedback_size(encoder);
    uint8_t* feedback = (uint8_t*) malloc(feedback_size);

    uint32_t i = 0;

    //Just for fun - fill data with random data
    for (; i < block_size; ++i)
    {
        data_in[i] = rand() % 256;
    }

    while (!kodo_is_complete(decoder))
    {
        printf("\n");

        if ((rand() % 2) && kodo_rank(encoder) < max_symbols)
        {
            uint32_t rank = kodo_rank(encoder);
            uint8_t* symbol = data_in + (rank * max_symbol_size);
            kodo_set_symbol(encoder, rank, symbol, max_symbol_size);
            printf("Symbol %d added to the encoder\n", rank);
        }

        if (kodo_rank(encoder) == 0)
        {
            continue;
        }

        kodo_write_payload(encoder, payload);

        printf("Packet encoded\n");

        if (rand() % 2)
        {
            printf("Packet dropped on channel\n");
            continue;
        }

        printf("Decoder received packet\n");

        kodo_read_payload(decoder, payload);

        if (kodo_has_trace(decoder))
        {
            printf("Trace decoder:\n");
            kodo_trace_callback(decoder, trace_callback);
        }

        printf("Encoder rank = %d\n", kodo_rank(encoder));
        printf("Decoder rank = %d\n", kodo_rank(decoder));

        printf("Decoder uncoded = %d\n", kodo_symbols_uncoded(decoder));
        printf("Decoder seen = %d\n", kodo_symbols_seen(decoder));

        kodo_write_feedback(decoder, feedback);

        if (rand() % 2)
        {
            printf("Lost feedback from decoder\n");
            continue;
        }

        printf("Received feedback from decoder\n");

        kodo_read_feedback(encoder, feedback);
    }

    uint8_t* data_out = (uint8_t*) malloc(kodo_block_size(decoder));
    kodo_copy_symbols(decoder, data_out, kodo_block_size(decoder));

    if (memcmp(data_in, data_out, block_size) == 0)
    {
        printf("Data decoded correctly\n");
    }
    else
    {
        printf("Unexpected failure to decode, please file a bug report :)\n");
    }

    free(data_in);
    free(data_out);
    free(payload);
    free(feedback);

    kodo_delete_encoder(encoder);
    kodo_delete_decoder(decoder);

    kodo_delete_encoder_factory(encoder_factory);
    kodo_delete_decoder_factory(decoder_factory);

    return 0;
}
