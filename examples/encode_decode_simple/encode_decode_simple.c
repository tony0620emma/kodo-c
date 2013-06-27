// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <ckodo/ckodo.h>
#include <stdint.h>

/// @example encode_decode_simple.c
///
/// Simple example showing how to encode and decode a block
/// of memory.

int main()
{
    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 42;
    uint32_t max_symbol_size = 160;

    // Here we select the coding algorithm we wish to use
    size_t algorithm = kodo_full_rlnc;

    // Here we select the finite field to use common choices are
    // kodo_binary, kodo_binary8, kodo_binary16
    size_t finite_field = kodo_binary;

    kodo_encoder_factory* encoder_factory =
        kodo_new_encoder_factory(algorithm, finite_field,
                                 max_symbols, max_symbol_size);

    kodo_decoder_factory* decoder_factory =
        kodo_new_decoder_factory(algorithm, finite_field,
                                 max_symbols, max_symbol_size);

    kodo_encoder* encoder = kodo_new_encoder(encoder_factory);
    kodo_decoder* decoder = kodo_new_decoder(decoder_factory);



    kodo_delete_encoder(encoder);
    kodo_delete_decoder(decoder);

    kodo_delete_encoder_factory(encoder_factory);
    kodo_delete_decoder_factory(decoder_factory);


    return 0;
}

