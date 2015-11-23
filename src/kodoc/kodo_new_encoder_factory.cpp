// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "kodoc.h"

#include <cstdint>
#include <cassert>

namespace kodoc
{
    // Forward declaration of factory functions
    kodo_factory_t new_fulcrum_encoder_factory(int32_t, uint32_t, uint32_t);
    kodo_factory_t new_full_vector_encoder_factory(int32_t, uint32_t, uint32_t);
    kodo_factory_t new_on_the_fly_encoder_factory(int32_t, uint32_t, uint32_t);
    kodo_factory_t new_perpetual_encoder_factory(int32_t, uint32_t, uint32_t);
    kodo_factory_t new_seed_encoder_factory(int32_t, uint32_t, uint32_t);
    kodo_factory_t new_sliding_window_encoder_factory(int32_t, uint32_t,
        uint32_t);
    kodo_factory_t new_sparse_full_vector_encoder_factory(int32_t, uint32_t,
        uint32_t);
    kodo_factory_t new_sparse_seed_encoder_factory(int32_t, uint32_t, uint32_t);
    kodo_factory_t new_reed_solomon_encoder_factory(int32_t, uint32_t,
        uint32_t);
}

kodo_factory_t kodo_new_encoder_factory(
    int32_t code_type, int32_t finite_field,
    uint32_t max_symbols, uint32_t max_symbol_size)
{
    using namespace kodoc;

    kodo_factory_t factory = 0;

    if (code_type == kodo_full_vector)
    {
        factory = new_full_vector_encoder_factory(
            finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_on_the_fly)
    {
        factory = new_on_the_fly_encoder_factory(
            finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_sliding_window)
    {
        factory = new_sliding_window_encoder_factory(
            finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_sparse_full_vector)
    {
        factory = new_sparse_full_vector_encoder_factory(
            finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_seed)
    {
        factory = new_seed_encoder_factory(
            finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_sparse_seed)
    {
        factory = new_sparse_seed_encoder_factory(
            finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_perpetual)
    {
        factory = new_perpetual_encoder_factory(
            finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_fulcrum)
    {
        factory = new_fulcrum_encoder_factory(
            finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_reed_solomon)
    {
        factory = new_reed_solomon_encoder_factory(
            finite_field, max_symbols, max_symbol_size);
    }

    // Unknown code type
    assert(factory && "Unknown code_type");
    return factory;
}
