// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#if !defined(KODOC_DISABLE_RLNC)

#include "kodoc.h"

#include <cstdint>

#include <kodo/api/api.hpp>
#include <kodo_rlnc/seed_encoder.hpp>
#include <kodo_rlnc/seed_decoder.hpp>

#include "create_factory.hpp"
#include "runtime_encoder.hpp"
#include "runtime_decoder.hpp"

namespace kodoc
{
    kodo_factory_t new_seed_encoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        return create_factory<
            runtime_encoder<
            kodo::rlnc::seed_encoder,
            kodo::api::systematic_binding>>(
                finite_field, max_symbols, max_symbol_size);
    }

    kodo_factory_t new_seed_decoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        return create_factory<
            runtime_decoder<
            kodo::rlnc::seed_decoder>>(
                finite_field, max_symbols, max_symbol_size);
    }
}

#endif
