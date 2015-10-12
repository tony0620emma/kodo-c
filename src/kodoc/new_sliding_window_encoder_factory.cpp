// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "kodoc.h"

#include <cstdint>

#include <kodo/api/api.hpp>
#include <kodo/rlnc/sliding_window_encoder.hpp>

#include "create_factory.hpp"
#include "kodoc_runtime_encoder.hpp"

namespace kodoc
{
    template<class Stack>
    using sliding_window_encoder_binding =
        kodo::api::read_feedback_binding<
        kodo::api::feedback_size_binding<
        kodo::api::systematic_binding<Stack>>>;

    kodo_factory_t new_sliding_window_encoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        using namespace kodo;

        return create_factory<
            kodoc_runtime_encoder<
            rlnc::sliding_window_encoder,
            sliding_window_encoder_binding>>(
                finite_field, max_symbols, max_symbol_size);
    }
}
