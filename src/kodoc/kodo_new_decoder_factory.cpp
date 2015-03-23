// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "kodoc.h"

#include <cstring>
#include <cstdint>
#include <cassert>

#include <kodo/rlnc/full_vector_codes.hpp>
#include <kodo/rlnc/on_the_fly_codes.hpp>
#include <kodo/rlnc/seed_codes.hpp>
#include <kodo/rlnc/sliding_window_decoder.hpp>

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

    if (code_type == kodo_full_rlnc)
    {
        if (trace_mode == kodo_trace_disabled)
        {
            if (finite_field == kodo_binary)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary4,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary8,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary16,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
        }
        else
        {
            if (finite_field == kodo_binary)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary4,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary8,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary16,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
        }
    }
    else if (code_type == kodo_on_the_fly)
    {
        if (trace_mode == kodo_trace_disabled)
        {
            if (finite_field == kodo_binary)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary4,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary8,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary16,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
        }
        else
        {
            if (finite_field == kodo_binary)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary4,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary8,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary16,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
        }
    }
    else if (code_type == kodo_sliding_window)
    {
        if (trace_mode == kodo_trace_disabled)
        {
            if (finite_field == kodo_binary)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary4,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary8,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary16,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
        }
        else
        {
            if (finite_field == kodo_binary)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary4,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary8,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary16,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
        }
    }

    // Unknown code type or field type
    assert(factory);

    return factory;
}
