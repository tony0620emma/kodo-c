// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodoc/kodoc.h>

#include <cstdint>

#include <gtest/gtest.h>

#include "test_helper.hpp"

static void test_encoder(uint32_t symbols, uint32_t symbol_size,
                         int32_t code_type, int32_t finite_field,
                         int32_t trace_enabled)
{
    kodo_factory_t encoder_factory =
        kodo_new_encoder_factory(code_type, finite_field,
                                 symbols, symbol_size,
                                 trace_enabled);

    kodo_coder_t encoder = kodo_factory_new_encoder(encoder_factory);

    // Coder methods

    EXPECT_EQ(symbols, kodo_symbols(encoder));
    EXPECT_EQ(symbol_size, kodo_symbol_size(encoder));
    EXPECT_EQ(symbols * symbol_size, kodo_block_size(encoder));
    EXPECT_GT(kodo_payload_size(encoder), symbol_size);
    EXPECT_EQ(0U, kodo_rank(encoder));

    if (code_type == kodo_full_rlnc ||
        code_type == kodo_on_the_fly)
    {
        EXPECT_TRUE(kodo_has_feedback_size(encoder) == 0);
    }
    else if (code_type == kodo_sliding_window)
    {
        EXPECT_TRUE(kodo_has_feedback_size(encoder) != 0);
        EXPECT_GT(kodo_feedback_size(encoder), 0U);
    }

    if (trace_enabled == kodo_trace_disabled)
    {
        EXPECT_TRUE(kodo_has_trace(encoder) == 0);
    }
    else if (trace_enabled == kodo_trace_enabled)
    {
        EXPECT_TRUE(kodo_has_trace(encoder) != 0);
        kodo_trace(encoder);
    }

    EXPECT_TRUE(kodo_has_write_payload(encoder) != 0);

    // Enoder methods

    EXPECT_TRUE(kodo_has_set_systematic_off(encoder) != 0);

    EXPECT_TRUE(kodo_is_systematic_on(encoder) != 0);
    kodo_set_systematic_off(encoder);
    EXPECT_TRUE(kodo_is_systematic_on(encoder) == 0);
    kodo_set_systematic_on(encoder);
    EXPECT_TRUE(kodo_is_systematic_on(encoder) != 0);

    kodo_delete_encoder(encoder);
    kodo_delete_encoder_factory(encoder_factory);
}

TEST(TestEncoder, invoke_api)
{
    uint32_t symbols = rand_symbols();
    uint32_t symbol_size = rand_symbol_size();

    test_combinations(
        test_encoder,
        symbols, symbol_size, kodo_trace_disabled);

    test_combinations(
        test_encoder,
        symbols, symbol_size, kodo_trace_enabled);
}
