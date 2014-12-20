// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodoc/kodoc.h>

#include <cstdlib>

#include <gtest/gtest.h>

#include "test_helper.hpp"

void test_basic_api(uint32_t max_symbols, uint32_t max_symbol_size,
                    int32_t code_type, int32_t finite_field)
{
    kodo_factory_t encoder_factory =
        kodo_new_encoder_factory(code_type, finite_field,
                                 max_symbols, max_symbol_size,
                                 kodo_trace_disabled);

    kodo_factory_t decoder_factory =
        kodo_new_decoder_factory(code_type, finite_field,
                                 max_symbols, max_symbol_size,
                                 kodo_trace_disabled);

    kodo_coder_t encoder = kodo_factory_new_encoder(encoder_factory);
    kodo_coder_t decoder = kodo_factory_new_decoder(decoder_factory);

    EXPECT_EQ(max_symbols,kodo_factory_max_symbols(encoder_factory));
    EXPECT_EQ(max_symbol_size,kodo_factory_max_symbol_size(encoder_factory));
    EXPECT_EQ(max_symbols, kodo_symbols(encoder));
    EXPECT_EQ(max_symbol_size,kodo_symbol_size(encoder));

    EXPECT_EQ(max_symbols, kodo_factory_max_symbols(decoder_factory));
    EXPECT_EQ(max_symbol_size, kodo_factory_max_symbol_size(decoder_factory));
    EXPECT_EQ(max_symbols, kodo_symbols(decoder));
    EXPECT_EQ(max_symbol_size, kodo_symbol_size(decoder));

    EXPECT_EQ(max_symbols * max_symbol_size, kodo_block_size(encoder));
    EXPECT_EQ(max_symbols * max_symbol_size, kodo_block_size(decoder));

    EXPECT_TRUE(kodo_factory_max_payload_size(encoder_factory) >=
                kodo_payload_size(encoder));

    EXPECT_TRUE(kodo_factory_max_payload_size(decoder_factory) >=
                kodo_payload_size(decoder));

    EXPECT_EQ(kodo_factory_max_payload_size(encoder_factory),
              kodo_factory_max_payload_size(decoder_factory));

    uint32_t payload_size = kodo_payload_size(encoder);
    uint8_t* payload = (uint8_t*) malloc(payload_size);

    uint32_t block_size = kodo_block_size(encoder);
    uint8_t* data_in = (uint8_t*) malloc(block_size);
    uint8_t* data_out = (uint8_t*) malloc(block_size);

    for(uint32_t i = 0; i < block_size; ++i)
        data_in[i] = rand() % 256;

    kodo_set_symbols(encoder, data_in, block_size);

    ASSERT_TRUE(kodo_is_complete(decoder) == 0);

    while (!kodo_is_complete(decoder))
    {
        kodo_encode(encoder, payload);
        kodo_decode(decoder, payload);
    }

    EXPECT_TRUE(kodo_is_complete(decoder) != 0);

    kodo_copy_symbols(decoder, data_out, block_size);

    EXPECT_EQ(memcmp(data_in, data_out, block_size), 0);

    free(data_in);
    free(data_out);
    free(payload);

    kodo_delete_encoder(encoder);
    kodo_delete_decoder(decoder);

    kodo_delete_encoder_factory(encoder_factory);
    kodo_delete_decoder_factory(decoder_factory);
}

TEST(TestFullRlncCodes, invoke_api)
{
    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    test_basic_api(max_symbols, max_symbol_size,
                   kodo_full_rlnc, kodo_binary);

    test_basic_api(max_symbols, max_symbol_size,
                   kodo_full_rlnc, kodo_binary8);

    test_basic_api(max_symbols, max_symbol_size,
                   kodo_full_rlnc, kodo_binary16);
}
