// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include "factory_wrapper.hpp"
#include "perpetual_encoder_wrapper.hpp"
#include "kodo_perpetual_encoder.hpp"

namespace kodo
{
    template<class KodoStack>
    class perpetual_encoder_factory_wrapper : public factory_wrapper<KodoStack>
    {
    public:

        using Super = factory_wrapper<KodoStack>;

        perpetual_encoder_factory_wrapper(uint32_t max_symbols,
                                          uint32_t max_symbol_size) :
            Super(max_symbols, max_symbol_size)
        { }

        virtual void* build()
        {
            using base_type = kodo_perpetual_encoder;

            auto encoder = m_factory.build();
            auto wrapper = new perpetual_encoder_wrapper<KodoStack, base_type>(
                encoder);

            return wrapper;
        }

    private:

        using Super::m_factory;
    };
}
