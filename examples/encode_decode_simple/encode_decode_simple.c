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
    uint32_t symbols = 42;
    uint32_t symbol_size = 160;

    kodo_codec* codec = kodo_new_codec();


    return 0;
}

