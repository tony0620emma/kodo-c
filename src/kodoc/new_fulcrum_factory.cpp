// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "kodoc.h"

#include <cstdint>

#include <kodo/rlnc/api/fulcrum_binding.hpp>
#include <kodo/rlnc/api/fulcrum_config_binding.hpp>
#include <kodo/rlnc/fulcrum_encoder.hpp>
#include <kodo/rlnc/fulcrum_combined_decoder.hpp>

#include "create_factory.hpp"
#include "runtime_encoder.hpp"
#include "runtime_decoder.hpp"

namespace kodoc
{
    kodo_factory_t new_fulcrum_encoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        return create_factory<
            runtime_encoder<
            kodo::rlnc::fulcrum_encoder,
            kodo::rlnc::api::fulcrum_binding,
            kodo::rlnc::api::fulcrum_config_binding>>(
                finite_field, max_symbols, max_symbol_size);
    }

    kodo_factory_t new_fulcrum_decoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        return create_factory<
            runtime_decoder<
            kodo::rlnc::fulcrum_combined_decoder,
            kodo::rlnc::api::fulcrum_binding,
            kodo::rlnc::api::fulcrum_config_binding>>(
                finite_field, max_symbols, max_symbol_size);
    }
}
