// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "kodoc.h"

#include <cstring>
#include <cstdint>
#include <cassert>

#include <kodo/rlnc/full_vector_decoder.hpp>
#include <kodo/rlnc/on_the_fly_decoder.hpp>
#include <kodo/rlnc/sliding_window_decoder.hpp>

#include "create_factory_wrapper.hpp"
#include "decoder_factory_wrapper.hpp"

//------------------------------------------------------------------
// DECODER FACTORY FOR DEEP STORAGE STACKS
//------------------------------------------------------------------

kodo_factory_t
kodo_new_decoder_factory(int32_t code_type, int32_t finite_field,
                         uint32_t max_symbols, uint32_t max_symbol_size,
                         int32_t trace_mode)
{
    using namespace kodo;
    using namespace kodo::rlnc;

    kodo_factory_t factory = 0;

    if (code_type == kodo_full_vector)
    {
        factory = create_factory_wrapper<
            decoder_factory_wrapper, full_vector_decoder>(
                finite_field, max_symbols, max_symbol_size, trace_mode);
    }
    else if (code_type == kodo_on_the_fly)
    {
        factory = create_factory_wrapper<
            decoder_factory_wrapper, on_the_fly_decoder>(
                finite_field, max_symbols, max_symbol_size, trace_mode);
    }
    else if (code_type == kodo_sliding_window)
    {
        factory = create_factory_wrapper<
            decoder_factory_wrapper, sliding_window_decoder>(
                finite_field, max_symbols, max_symbol_size, trace_mode);
    }

    // Unknown code type
    assert(factory);

    return factory;
}
