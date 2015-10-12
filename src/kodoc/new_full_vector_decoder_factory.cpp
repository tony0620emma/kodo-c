// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "kodoc.h"

#include <cstdint>

#include <kodo/api/api.hpp>
#include <kodo/rlnc/full_vector_decoder.hpp>

#include "create_factory.hpp"
#include "kodoc_runtime_decoder.hpp"

namespace kodoc
{
    kodo_factory_t new_full_vector_decoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        using namespace kodo;

        return create_factory<
            kodoc_runtime_decoder<
            rlnc::full_vector_decoder,
            api::write_payload_binding>>(
                finite_field, max_symbols, max_symbol_size);
    }
}
