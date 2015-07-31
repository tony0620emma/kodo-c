// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "kodoc.h"

#include <cstdint>
#include <cassert>

#include <fifi/default_field.hpp>

#include <kodo/enable_trace.hpp>


template<template<class> class Wrapper, template<class, class> class Coder>
kodo_factory_t
create_factory_wrapper(int32_t finite_field, uint32_t max_symbols,
                       uint32_t max_symbol_size, int32_t trace_mode)
{
    using namespace kodo;

    kodo_factory_t factory = 0;

    if (trace_mode == kodo_trace_disabled)
    {
        if (finite_field == kodo_binary)
        {
            factory = new Wrapper<Coder<fifi::binary, meta::typelist<>>>(
                max_symbols, max_symbol_size);
        }
        else if (finite_field == kodo_binary4)
        {
            factory = new Wrapper<Coder<fifi::binary4, meta::typelist<>>>(
                max_symbols, max_symbol_size);
        }
        else if (finite_field == kodo_binary8)
        {
            factory = new Wrapper<Coder<fifi::binary8, meta::typelist<>>>(
                max_symbols, max_symbol_size);
        }
        else if (finite_field == kodo_binary16)
        {
            factory = new Wrapper<Coder<fifi::binary16, meta::typelist<>>>(
                max_symbols, max_symbol_size);
        }
    }
    else
    {
        if (finite_field == kodo_binary)
        {
            factory = new Wrapper<Coder<fifi::binary,
                meta::typelist<kodo::enable_trace>>>(
                    max_symbols, max_symbol_size);
        }
        else if (finite_field == kodo_binary4)
        {
            factory = new Wrapper<Coder<fifi::binary4,
                meta::typelist<kodo::enable_trace>>>(
                    max_symbols, max_symbol_size);
        }
        else if (finite_field == kodo_binary8)
        {
            factory = new Wrapper<Coder<fifi::binary8,
                meta::typelist<kodo::enable_trace>>>(
                    max_symbols, max_symbol_size);
        }
        else if (finite_field == kodo_binary16)
        {
            factory = new Wrapper<Coder<fifi::binary16,
                meta::typelist<kodo::enable_trace>>>(
                    max_symbols, max_symbol_size);
        }
    }

    // Unknown field type
    assert(factory);

    return factory;
}
