// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <ckodo/ckodo.h>

/// @example use_trace_layers.c
///
/// Simple example showing how to use some of the trace layers defined
/// in Kodo.

uint8_t filter_function(const char* zone)
{
    char* zones[] = {"decoder_state", "input_symbol_coefficients", NULL};
    char** cmp = zones;
    while (*cmp)
    {
        if (!strcmp(zone, *cmp))
            return 1;
        cmp++;
    }
    return 0;
}

int main()
{

    //seed rand
    srand(time(NULL));

    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 8;
    uint32_t max_symbol_size = 33;


    size_t algorithm = kodo_full_rlnc;
    size_t finite_field = kodo_binary8;


    // In the following we will make an encoder/decoder factory.
    // The factories are used to build actual encoders/decoder
    kodo_factory_t* encoder_factory =
        kodo_new_encoder_factory(algorithm, finite_field,
                                   max_symbols, max_symbol_size,
                                   kodo_trace_disabled);

    kodo_factory_t* decoder_factory =
        kodo_new_decoder_factory(algorithm, finite_field,
                                 max_symbols, max_symbol_size,
                                 kodo_trace_enabled);

    // If we wanted to build an encoder or decoder with a smaller number of
    // symbols or a different symbol size, then this can be adjusted using the
    // following functions:
    //      kodo_factory_set_symbols(...)
    //      kodo_factory_set_symbol_size(...)
    // We cannot exceed the maximum values which was used when building
    // the factory.
    kodo_coder_t* encoder = kodo_factory_new_encoder(encoder_factory);
    kodo_coder_t* decoder = kodo_factory_new_decoder(decoder_factory);

    // Allocate some storage for a "payload" the payload is what we would
    // eventually send over a network
    uint32_t payload_size = kodo_payload_size(encoder);
    uint8_t* payload = (uint8_t*) malloc(payload_size);

    // Allocate some data to encode. In this case we make a buffer
    // with the same size as the encoder's block size (the max.
    // amount a single encoder can encode)
    uint32_t block_size = kodo_block_size(encoder);
    uint8_t* data_in = (uint8_t*) malloc(block_size);

    // Just for fun - fill the data with random data
    uint32_t i = 0;
    for (; i < block_size; ++i)
    {
        data_in[i] = rand() % 256;
    }

    kodo_set_symbols(encoder, data_in, block_size);

    while(!kodo_is_complete(decoder))
    {
        kodo_encode(encoder, payload);
        if(kodo_has_trace(encoder))
        {
            printf("Trace encoder:\n");
            kodo_trace(encoder);
        }

        if ((rand() % 2) == 0)
        {
            continue;
        }

        kodo_decode(decoder, payload);

        printf("Trace decoder:\n");
        if (kodo_has_trace(decoder))
        {
            kodo_trace_filter(decoder, &filter_function);
        }

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

    kodo_delete_encoder(encoder);
    kodo_delete_decoder(decoder);

    kodo_delete_encoder_factory(encoder_factory);
    kodo_delete_decoder_factory(decoder_factory);

    return 0;
}
