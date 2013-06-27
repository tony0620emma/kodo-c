// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "coder.hpp"

namespace kodo
{
    struct decoder : public coder
    {
        virtual void decode(uint8_t *) = 0;
        virtual bool is_complete() const = 0;
        virtual uint32_t rank() const = 0;

        virtual void copy_symbols(uint8_t* data, uint32_t size) const = 0;


        virtual ~decoder(){}
    };
}


