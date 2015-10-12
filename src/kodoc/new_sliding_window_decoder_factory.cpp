// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "kodoc.h"

#include <cstdint>

#include <kodo/api/api.hpp>
#include <kodo/rlnc/sliding_window_decoder.hpp>

#include "create_factory.hpp"
#include "kodoc_runtime_decoder.hpp"

namespace kodoc
{
    template<class Stack>
    using sliding_window_decoder_binding =
        kodo::api::write_feedback_binding<
        kodo::api::feedback_size_binding<
        kodo::api::partial_decoding_binding<
        kodo::api::write_payload_binding<Stack>>>>;

    kodo_factory_t new_sliding_window_decoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        using namespace kodo;
        return create_factory<
            kodoc_runtime_decoder<
            rlnc::sliding_window_decoder,
            sliding_window_decoder_binding>>(
                finite_field, max_symbols, max_symbol_size);
    }
}
