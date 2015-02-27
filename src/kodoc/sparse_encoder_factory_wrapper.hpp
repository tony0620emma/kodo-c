// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "encoder_factory_wrapper.hpp"
#include "sparse_encoder_wrapper.hpp"

#include "sparse_encoder.hpp"

namespace kodo
{
    template<class KodoStack>
    class sparse_encoder_factory_wrapper : public
        encoder_factory_wrapper<KodoStack>
    {
    public:

        using Super = encoder_factory_wrapper<KodoStack>;

        sparse_encoder_factory_wrapper(uint32_t max_symbols,
                                       uint32_t max_symbol_size) :
            Super(max_symbols, max_symbol_size)
        { }

        virtual void* build()
        {
            using base_type = kodo_sparse_encoder;

            auto encoder = m_factory.build();
            auto wrapper =
                new sparse_encoder_wrapper<KodoStack, base_type>(encoder);

            return wrapper;
        }

    private:

        using Super::m_factory;
    };
}
