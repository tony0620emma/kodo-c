// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "kodoc.h"

#include <cstdint>
#include <map>
#include <string>

template<class Runtime>
kodo_factory_t create_factory(int32_t finite_field, uint32_t max_symbols,
                              uint32_t max_symbol_size)
{
    std::map<int32_t, std::string> finite_field_map =
    {
        {kodo_binary, "binary"},
        {kodo_binary4, "binary4"},
        {kodo_binary8, "binary8"}
    };

    auto r = Runtime();

    r.set_field(finite_field_map[finite_field]);

    auto f = r.build(max_symbols, max_symbol_size);

    return (kodo_factory_t)f->keep_alive();
}
