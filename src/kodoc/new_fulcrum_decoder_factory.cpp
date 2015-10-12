// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "kodoc.h"

#include <cstdint>

#include <kodo/rlnc/api/fulcrum_binding.hpp>
#include <kodo/rlnc/api/fulcrum_config_binding.hpp>
#include <kodo/rlnc/fulcrum_combined_decoder.hpp>

#include "create_factory.hpp"
#include "kodoc_runtime_decoder.hpp"

namespace kodoc
{
    kodo_factory_t new_fulcrum_decoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        using namespace kodo;

        return create_factory<
            kodoc_runtime_decoder<
            rlnc::fulcrum_combined_decoder,
            rlnc::api::fulcrum_binding,
            rlnc::api::fulcrum_config_binding>>(
                finite_field, max_symbols, max_symbol_size);
    }
}
