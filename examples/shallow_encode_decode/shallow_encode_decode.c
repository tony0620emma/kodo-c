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

/// @example shallow_encode_decode.c
///
/// Example showing how to encode and decode symbols that are stored in
/// non-contiguous memory buffers.

void trace_callback(const char* zone, const char* data)
{
    if (strcmp(zone, "decoder_state") == 0)
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
    uint32_t symbols = 10;
    uint32_t symbol_size = 100;

    // Here we select the coding code_type we wish to use
    int32_t code_type = kodo_full_rlnc;

    // Here we select the finite field to use common choices are
    // kodo_binary, kodo_binary8, kodo_binary16
    int32_t finite_field = kodo_binary;

    kodo_factory_t encoder_factory =
        kodo_new_shallow_encoder_factory(code_type, finite_field,
                                         symbols, symbol_size,
                                         kodo_trace_disabled);

    kodo_factory_t decoder_factory =
        kodo_new_shallow_decoder_factory(code_type, finite_field,
                                         symbols, symbol_size,
                                         kodo_trace_enabled);

    // If we wanted to build an encoder of decoder with a smaller number of
    // symbols or a different symbol size, then this can be adjusted using the
    // following functions:
    // kodo_factory_set_symbols(...) and kodo_factory_set_symbol_size(...)
    // We can however not exceed the maximum values which were used when
    // building the factory.

    kodo_coder_t encoder = kodo_factory_new_encoder(encoder_factory);
    kodo_coder_t decoder = kodo_factory_new_decoder(decoder_factory);

    uint32_t bytes_used;
    uint32_t payload_size = kodo_payload_size(encoder);
    uint8_t* payload = (uint8_t*) malloc(payload_size);

    // Allocate symbols in non-contiguous buffers
    uint8_t** input_symbols = (uint8_t**) malloc(symbols * sizeof(uint8_t*));
    uint8_t** output_symbols = (uint8_t**) malloc(symbols * sizeof(uint8_t*));

    uint32_t i, j;
    for (i = 0; i < symbols; ++i)
    {
        // Create the individual symbols for the encoder
        input_symbols[i] = (uint8_t*) malloc(symbol_size);

        // Randomize input data
        for (j = 0; j < symbol_size; ++j)
            input_symbols[i][j] = rand() % 256;

        // Store the symbol pointer in the encoder
        kodo_set_symbol(encoder, i, input_symbols[i], symbol_size);

        // Create the output symbol buffers for the decoder
        output_symbols[i] = (uint8_t*) malloc(symbol_size);

        // Specify the output buffers used for decoding
        kodo_set_symbol(decoder, i, output_symbols[i], symbol_size);
    }

    // Most of the network coding algorithms supports a mode of operation
    // which is known as systematic coding. This basically means that
    // initially all symbols are sent once un-coded. The rationale behind this
    // is that if no errors occur during the transmission we will not have
    // performed any unnecessary coding operations. An encoder will exit the
    // systematic phase automatically once all symbols have been sent un-coded
    // once.
    //
    // With Kodo we can ask an encoder whether it supports systematic encoding
    // or not using the following functions:

    if (kodo_has_systematic_encoder(encoder) && kodo_is_systematic_on(encoder))
    {
        printf("Systematic encoding enabled\n");
    }
    else
    {
        printf("Systematic encoding disabled\n");
    }

    // If we do not wish to use systematic encoding, but to do full coding
    // from the beginning we can turn systematic coding off using the following
    // API:
    //
    // if (kodo_has_systematic_encoder(encoder))
    // {
    //    kodo_set_systematic_off(encoder);
    // }

    while (!kodo_is_complete(decoder))
    {
        // The encoder will use a certain amount of bytes of the payload
        // buffer. It will never use more than payload_size, but it might
        // use less.
        bytes_used = kodo_write_payload(encoder, payload);
        printf("Payload generated by encoder, rank = %d, bytes used = %d\n",
               kodo_rank(encoder), bytes_used);

        // Simulate a channel with a 50% loss rate to demonstrate the
        // recovery of lost symbols
        if (rand() % 2)
        {
            printf("Packet dropped on channel\n\n");
            continue;
        }

        // Pass the generated packet to the decoder
        kodo_read_payload(decoder, payload);
        printf("Payload processed by decoder, current rank = %d\n\n",
               kodo_rank(decoder));

        if (kodo_has_trace(decoder))
        {
            kodo_trace_callback(decoder, trace_callback);
        }
    }

    // Compare the input and output symbols one-by-one
    uint32_t failures = 0;
    for (i = 0; i < symbols; ++i)
    {
        if (memcmp(input_symbols[i], output_symbols[i], symbol_size) != 0)
        {
            printf("Error: Symbol %d was not decoded correctly\n", i);
            failures++;
        }

        free(input_symbols[i]);
        free(output_symbols[i]);
    }

    if (failures == 0)
    {
        printf("Data decoded correctly\n");
    }


    free(input_symbols);
    free(output_symbols);
    free(payload);

    kodo_delete_encoder(encoder);
    kodo_delete_decoder(decoder);

    kodo_delete_encoder_factory(encoder_factory);
    kodo_delete_decoder_factory(decoder_factory);

    return 0;
}
