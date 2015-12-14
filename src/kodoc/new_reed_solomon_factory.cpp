// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#if !defined(KODOC_DISABLE_REED_SOLOMON)

#include "kodoc.h"

#include <cstdint>

#include <kodo/api/api.hpp>
#include <kodo_reed_solomon/codes.hpp>

#include "create_factory.hpp"
#include "runtime_encoder.hpp"
#include "runtime_decoder.hpp"

namespace kodoc
{
    kodo_factory_t new_reed_solomon_encoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        return create_factory<
            runtime_encoder<
            kodo::reed_solomon::encoder,
            kodo::api::systematic_binding>>(
                finite_field, max_symbols, max_symbol_size);
    }

    kodo_factory_t new_reed_solomon_decoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        return create_factory<
            runtime_decoder<
            kodo::reed_solomon::decoder>>(
                finite_field, max_symbols, max_symbol_size);
    }
}

#endif
