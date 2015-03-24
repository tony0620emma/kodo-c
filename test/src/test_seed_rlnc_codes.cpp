// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <kodoc/kodoc.h>

#include <gtest/gtest.h>

#include "test_helper.hpp"
#include "test_shallow_api.hpp"

TEST(TestSeedRlncCodes, shallow_api)
{
    uint32_t max_symbols = rand_symbols();
    uint32_t max_symbol_size = rand_symbol_size();

    test_shallow_api(kodo_seed_rlnc, max_symbols, max_symbol_size);
}

TEST(TestSeedRlncCodes, sparse_shallow_api)
{
    // Make sure that the decoding can complete with a lower density
    uint32_t max_symbols = rand_symbols() + 10;
    uint32_t max_symbol_size = rand_symbol_size();

    test_shallow_api(kodo_sparse_seed_rlnc, kodo_sparse_seed_rlnc,
                     max_symbols, max_symbol_size);
}
