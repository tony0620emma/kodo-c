// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "kodoc.h"

#include <cstring>
#include <cstdint>
#include <cassert>

#include <kodo/rlnc/full_vector_encoder.hpp>
#include <kodo/rlnc/on_the_fly_encoder.hpp>
#include <kodo/rlnc/perpetual_encoder.hpp>
#include <kodo/rlnc/seed_codes.hpp>
#include <kodo/rlnc/sliding_window_encoder.hpp>
#include <kodo/rlnc/sparse_full_vector_encoder.hpp>

#include "create_factory_wrapper.hpp"

#include "encoder_factory_wrapper.hpp"
#include "sparse_encoder_factory_wrapper.hpp"
#include "perpetual_encoder_factory_wrapper.hpp"

//------------------------------------------------------------------
// ENCODER FACTORY FOR DEEP STORAGE STACKS
//------------------------------------------------------------------

kodo_factory_t
kodo_new_encoder_factory(int32_t code_type, int32_t finite_field,
                         uint32_t max_symbols, uint32_t max_symbol_size)
{
    using namespace kodo;
    using namespace kodo::rlnc;

    kodo_factory_t factory = 0;

    if (code_type == kodo_full_vector)
    {
        factory = create_factory_wrapper<
            encoder_factory_wrapper, full_vector_encoder,
            meta::typelist<storage_type<tag::const_shallow_storage>>>(
                finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_sparse_full_vector)
    {
        factory = create_factory_wrapper<
            sparse_encoder_factory_wrapper, sparse_full_vector_encoder,
            meta::typelist<storage_type<tag::const_shallow_storage>>>(
                finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_on_the_fly)
    {
        factory = create_factory_wrapper<
            encoder_factory_wrapper, on_the_fly_encoder,
            meta::typelist<storage_type<tag::const_shallow_storage>>>(
                finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_sliding_window)
    {
        factory = create_factory_wrapper<
            encoder_factory_wrapper, sliding_window_encoder,
            meta::typelist<storage_type<tag::const_shallow_storage>>>(
                finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_seed)
    {
        factory = create_factory_wrapper<
            encoder_factory_wrapper, seed_encoder,
            meta::typelist<storage_type<tag::const_shallow_storage>>>(
            finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_sparse_seed)
    {
        factory = create_factory_wrapper<
            sparse_encoder_factory_wrapper, sparse_seed_encoder,
            meta::typelist<storage_type<tag::const_shallow_storage>>>(
                finite_field, max_symbols, max_symbol_size);
    }
    else if (code_type == kodo_perpetual)
    {
        factory = create_factory_wrapper<
            perpetual_encoder_factory_wrapper, perpetual_encoder,
            meta::typelist<storage_type<tag::const_shallow_storage>>>(
                finite_field, max_symbols, max_symbol_size);
    }

    // Unknown code type
    assert(factory);

    return factory;
}
