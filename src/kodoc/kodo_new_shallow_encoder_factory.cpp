// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "kodoc.h"

#include <cstring>
#include <cstdint>
#include <cassert>

#include <kodo/rlnc/full_vector_codes.hpp>
#include <kodo/rlnc/seed_codes.hpp>

#include "create_factory_wrapper.hpp"

#include "encoder_factory_wrapper.hpp"
#include "sparse_encoder_factory_wrapper.hpp"

//------------------------------------------------------------------
// ENCODER FACTORY FOR SHALLOW STORAGE STACKS
//------------------------------------------------------------------

kodo_factory_t
kodo_new_shallow_encoder_factory(int32_t code_type, int32_t finite_field,
                                 uint32_t max_symbols, uint32_t max_symbol_size,
                                 int32_t trace_mode)
{
    using namespace kodo;
    using namespace kodo::rlnc;

    kodo_factory_t factory = 0;

    if (code_type == kodo_full_rlnc)
    {
        factory = create_factory_wrapper<
            encoder_factory_wrapper, shallow_full_vector_encoder>(
                finite_field, max_symbols, max_symbol_size, trace_mode);
    }
    else if (code_type == kodo_sparse_full_rlnc)
    {
        factory = create_factory_wrapper<
            sparse_encoder_factory_wrapper, shallow_sparse_full_vector_encoder>(
                finite_field, max_symbols, max_symbol_size, trace_mode);
    }
    else if (code_type == kodo_seed_rlnc)
    {
        factory = create_factory_wrapper<
            encoder_factory_wrapper, shallow_seed_encoder>(
                finite_field, max_symbols, max_symbol_size, trace_mode);
    }

    // Unknown code type
    assert(factory);

    return factory;
}
