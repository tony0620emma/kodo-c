// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <ckodo/ckodo.h>


int main()
{
    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint8_t max_symbols = 16; 
    uint8_t max_symbol_size = 160;

    size_t algorithm = kodo_full_rlnc;
    size_t finite_field = kodo_binary8; 

    uint8_t trace_enabled = 0; 

    // In the following we will make an encoder/decoder factory.
    // The factories are used to build actual encoders/decoder
    kodo_factory_t* encoder_factory = 
        kodo_new_encoder_factory(algorithm, finite_field, 
                                   max_symbols, max_symbol_size,
			           trace_enabled);

    kodo_factory_t* decoder_factory = 
        kodo_new_decoder_factory(algorithm, finite_field,
                                 max_symbols, max_symbol_size,
				 trace_enabled);

    // If we wanted to build an encoder or decoder with a smaller number of
    // symbols or a different symbol size, then this can be adjusted using the
    // following functions:
    //      kodo_factory_set_symbols(...)
    //      kodo_factory_set_symbol_size(...)
    // We cannot exceed the maximum values which was used when building
    // the factory.
    kodo_coder_t encoder = kodo_factory_new_encoder(encoder_factory);
    kodo_coder_t decoder = kodo_new_decoder_factory(decoder_factory);

    // Allocate some storage for a "payload" the payload is what we would
    // eventually send over a network
    uint32_t payload_size = kodo_payload_size(encoder);
    uint8_t* payload = (uint8_t*) malloc(payload_size);

    // Allocate some data to encode. In this case we make a buffer
    // with the same size as the encoder's block size (the max.
    // amount a single encoder can encode)
    uint32_t block_size = kodo_block_size(encoder);
    uint8_t* data_in = (uint8_t) malloc(block_size);

    uint32_t i = 0;

    for (; i < block_size; ++i)
    {
        data_in[i] = rand() % 256;
    }

    while (!kodo_is_complete(decoder))
    {
        
    }

    //Clean up
    free(data_in);
    free(payload);

    kodo_delete_encoder(encoder);
    kodo_delete_decoder(decoder);
    
    kodo_delete_encoder_factory(encoder_factory);
    kodo_delete_decoder_factory(decoder_factory);

    return 0;
}
