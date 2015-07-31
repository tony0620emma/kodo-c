// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cstdlib>

#include <gtest/gtest.h>

#include <kodoc/kodoc.h>

inline void run_test_basic_api(int32_t code_type, int32_t finite_field,
                               uint32_t symbols, uint32_t symbol_size)
{
    kodo_factory_t encoder_factory =
        kodo_new_encoder_factory(code_type, finite_field,
                                 symbols, symbol_size,
                                 kodo_trace_disabled);

    kodo_factory_t decoder_factory =
        kodo_new_decoder_factory(code_type, finite_field,
                                 symbols, symbol_size,
                                 kodo_trace_disabled);

    kodo_coder_t encoder = kodo_factory_new_encoder(encoder_factory);
    kodo_coder_t decoder = kodo_factory_new_decoder(decoder_factory);

    EXPECT_EQ(symbols, kodo_factory_max_symbols(encoder_factory));
    EXPECT_EQ(symbol_size, kodo_factory_max_symbol_size(encoder_factory));
    EXPECT_EQ(symbols, kodo_symbols(encoder));
    EXPECT_EQ(symbol_size, kodo_symbol_size(encoder));

    EXPECT_EQ(symbols, kodo_factory_max_symbols(decoder_factory));
    EXPECT_EQ(symbol_size, kodo_factory_max_symbol_size(decoder_factory));
    EXPECT_EQ(symbols, kodo_symbols(decoder));
    EXPECT_EQ(symbol_size, kodo_symbol_size(decoder));

    EXPECT_EQ(symbols * symbol_size, kodo_block_size(encoder));
    EXPECT_EQ(symbols * symbol_size, kodo_block_size(decoder));

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

    EXPECT_TRUE(kodo_is_complete(decoder) == 0);

    while (!kodo_is_complete(decoder))
    {
        kodo_write_payload(encoder, payload);
        kodo_read_payload(decoder, payload);
    }

    EXPECT_TRUE(kodo_is_complete(decoder) != 0);

    kodo_copy_from_symbols(decoder, data_out, block_size);

    EXPECT_EQ(memcmp(data_in, data_out, block_size), 0);

    free(data_in);
    free(data_out);
    free(payload);

    kodo_delete_encoder(encoder);
    kodo_delete_decoder(decoder);

    kodo_delete_encoder_factory(encoder_factory);
    kodo_delete_decoder_factory(decoder_factory);
}

inline void test_basic_api(int32_t code_type, uint32_t symbols,
                           uint32_t symbol_size)
{
    SCOPED_TRACE(testing::Message() << "symbols = " << symbols);
    SCOPED_TRACE(testing::Message() << "symbol_size = " << symbol_size);

    {
        SCOPED_TRACE(testing::Message() << "field = binary");
        run_test_basic_api(code_type, kodo_binary, symbols, symbol_size);
    }

    {
        SCOPED_TRACE(testing::Message() << "field = binary4");
        run_test_basic_api(code_type, kodo_binary4, symbols, symbol_size);
    }

    {
        SCOPED_TRACE(testing::Message() << "field = binary8");
        run_test_basic_api(code_type, kodo_binary8, symbols, symbol_size);
    }

    {
        SCOPED_TRACE(testing::Message() << "field = binary16");
        run_test_basic_api(code_type, kodo_binary16, symbols, symbol_size);
    }
}
