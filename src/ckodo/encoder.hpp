// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "coder.hpp"

namespace kodo
{
    struct encoder : public coder
    {
        virtual uint32_t encode(uint8_t *) = 0;

        virtual void set_symbols(
            const uint8_t* data, uint32_t size) = 0;

        virtual void set_symbol(
            uint32_t index, const uint8_t* data, uint32_t size) = 0;

        virtual ~encoder(){}
    };
}


