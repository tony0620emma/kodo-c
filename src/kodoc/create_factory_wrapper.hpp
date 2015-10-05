// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "kodoc.h"

#include <cstdint>
#include <cassert>

#include <fifi/default_field.hpp>

#include <meta/typelist.hpp>

#include <kodo/enable_trace.hpp>
#include <kodo/storage_type.hpp>


template<
    template<class> class Wrapper,
    template<class, class, class...> class Coder,
    class Features
>
kodo_factory_t
create_factory_wrapper(int32_t finite_field, uint32_t max_symbols,
                       uint32_t max_symbol_size)
{
    using namespace kodo;

    kodo_factory_t factory = 0;

    if (finite_field == kodo_binary)
    {
        factory = new Wrapper<Coder<fifi::binary,
            typename Features::template append<kodo::enable_trace>>>(
                max_symbols, max_symbol_size);
    }
    else if (finite_field == kodo_binary4)
    {
        factory = new Wrapper<Coder<fifi::binary4,
            typename Features::template append<kodo::enable_trace>>>(
                max_symbols, max_symbol_size);
    }
    else if (finite_field == kodo_binary8)
    {
        factory = new Wrapper<Coder<fifi::binary8,
            typename Features::template append<kodo::enable_trace>>>(
                max_symbols, max_symbol_size);
    }

    // Unknown field type
    assert(factory);

    return factory;
}
