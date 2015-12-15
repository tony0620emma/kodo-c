// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodoc/kodoc.h>

#include <functional>

#include <gtest/gtest.h>

#include "test_helper.hpp"
#include "test_basic_api.hpp"

TEST(test_fulcrum_codes, basic_api)
{
    if (kodo_has_codec(kodo_fulcrum) == false)
        return;

    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    test_basic_api(kodo_fulcrum, max_symbols, max_symbol_size);
}

static void test_fulcrum_api(kodo_factory_t fulcrum_factory,
    std::function<kodo_coder_t (kodo_factory_t)> build_coder)
{
    uint32_t max_expansion = kodo_factory_max_expansion(fulcrum_factory);

    EXPECT_EQ(10U, max_expansion);

    kodo_factory_set_expansion(fulcrum_factory, max_expansion);

    kodo_coder_t coder = build_coder(fulcrum_factory);
    EXPECT_TRUE(coder != 0);
    EXPECT_EQ(max_expansion, kodo_expansion(coder));
    kodo_delete_coder(coder);

    uint32_t other_expansion = max_expansion / 2;
    kodo_factory_set_expansion(fulcrum_factory, other_expansion);

    kodo_coder_t other_coder = build_coder(fulcrum_factory);
    EXPECT_TRUE(other_coder != 0);
    EXPECT_EQ(other_expansion, kodo_expansion(other_coder));
    kodo_delete_coder(other_coder);
}

TEST(test_fulcrum_codes, fulcrum_encoder_api)
{
    if (kodo_has_codec(kodo_fulcrum) == false)
        return;

    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    kodo_factory_t encoder_factory = kodo_new_encoder_factory(
        kodo_fulcrum, kodo_binary8, max_symbols, max_symbol_size);
    test_fulcrum_api(encoder_factory, kodo_factory_new_encoder);
    kodo_delete_factory(encoder_factory);
}

TEST(test_fulcrum_codes, fulcrum_decoder_api)
{
    if (kodo_has_codec(kodo_fulcrum) == false)
        return;

    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    kodo_factory_t decoder_factory = kodo_new_decoder_factory(
        kodo_fulcrum, kodo_binary8, max_symbols, max_symbol_size);
    test_fulcrum_api(decoder_factory, kodo_factory_new_decoder);
    kodo_delete_factory(decoder_factory);
}
