// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "factory.hpp"

namespace kodo
{

    template<class KodoStack>
    struct factory_wrapper : public factory
    {
        factory_wrapper(uint32_t max_symbols,
                        uint32_t max_symbol_size)
            : m_factory(max_symbols, max_symbol_size)
        { }

        virtual uint32_t max_symbols() const
        {
            return m_factory.max_symbols();
        }

        virtual uint32_t max_symbol_size() const
        {
            return m_factory.max_symbol_size();
        }

        virtual uint32_t max_block_size() const
        {
            return m_factory.max_block_size();
        }

        virtual uint32_t max_payload_size() const
        {
            return m_factory.max_payload_size();
        }

        typename KodoStack::factory m_factory;
    };
}


