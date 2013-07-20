// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <ckodo/ckodo.h>
#include <stdint.h>

/// @example encode_decode_on_the_fly.c
///
/// This example shows how to use a storage aware encoder which will
/// allow you to encode from a block before all symbols have been
/// specified. This can be useful in cases where the symbols that
/// should be encoded are produced on-the-fly. The decoder will also
/// allow you to detect whether the symbols have been partially decoded.

int main()
{
    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t symbols = 42;
    uint32_t symbol_size = 160;

    // Here we select the coding algorithm we wish to use
    size_t algorithm = kodo_on_the_fly;

    // Here we select the finite field to use common choices are
    // kodo_binary, kodo_binary8, kodo_binary16
    size_t finite_field = kodo_binary;

    kodo_factory_t* encoder_factory =
        kodo_new_encoder_factory(algorithm, finite_field,
                                 max_symbols, max_symbol_size);

    kodo_factory_t* decoder_factory =
        kodo_new_decoder_factory(algorithm, finite_field,
                                 max_symbols, max_symbol_size);

    kodo_coder_t* encoder = kodo_factory_new_encoder(encoder_factory);
    kodo_coder_t* decoder = kodo_factory_new_decoder(decoder_factory);

    uint32_t payload_size = kodo_payload_size(encoder);
    uint8_t *payload = (uint8_t*) malloc(payload_size);

    uint32_t block_size = kodo_block_size(encoder);
    uint8_t *data_in = (uint8_t*) malloc(block_size);
    uint8_t *data_out = (uint8_t*) malloc(block_size);

    uint32_t i = 0;
    for(; i < block_size; ++i)
        data_in[i] = rand() % 256;

    // Notice that we are starting the encoding / decoding loop without having
    // added any data to the encoder - we will do this on the fly in the loop
    // below

    while(!kodo_is_complete(decoder))
    {
        uint32_t bytes_used = kodo_encode(encoder, payload);
        printf("payload encoded, bytes used = %d", bytes_used);

        // Send the data to the decoders, here we just for fun
        // simulate that we are loosing 50% of the packets
        if((rand() % 2) == 0)
           continue;

        // Packet got through - pass that packet to the decoder
        kodo_decode(decoder, payload);

        printf("payload decoded, decoding rank %d", kodo_rank(decoder));

        // Randomly choose to insert a symbol (50% of the time)
        if((rand() % 2) == 0 && kodo_rank(encoder) < symbols)
        {
            // For an encoder the rank specifies the number of symbols
            // it has available for encoding
            uint32_t rank = kodo_rank(encoder);

            // Calculate the offset to the next symbol to insert
            uint8_t* symbol = rank * kodo_symbol_size(encoder);
            kodo_set_symbol(encoder, rank, symbol, kodo_symbol_size(encoder));
        }
    }

    kodo_copy_symbols(decoder, data_out, block_size);

    if(memcmp(data_in, data_out, block_size) == 0)
    {
        printf("Data decoded correctly\n");
    }
    else
    {
        printf("Unexpected failure to decode please file a bug report :)\n");
    }

    free((void*)data_in);
    free((void*)data_out);
    free((void*)payload);

    kodo_delete_encoder(encoder);
    kodo_delete_decoder(decoder);

    kodo_delete_encoder_factory(encoder_factory);
    kodo_delete_decoder_factory(decoder_factory);

    return 0;
}

