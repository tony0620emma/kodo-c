// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#if !defined(KODOC_DISABLE_RLNC) && !defined(KODOC_DISABLE_SLIDING_WINDOW)

#include "kodoc.h"

#include <cstdint>

#include <kodo/api/api.hpp>
#include <kodo_rlnc/sliding_window_encoder.hpp>
#include <kodo_rlnc/sliding_window_decoder.hpp>

#include "create_factory.hpp"
#include "runtime_encoder.hpp"
#include "runtime_decoder.hpp"

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
        return create_factory<
            runtime_encoder<
            kodo::rlnc::sliding_window_encoder,
            sliding_window_encoder_binding>>(
                finite_field, max_symbols, max_symbol_size);
    }

    template<class Stack>
    using sliding_window_decoder_binding =
        kodo::api::write_feedback_binding<
        kodo::api::feedback_size_binding<
        kodo::api::partial_decoding_binding<
        kodo::api::write_payload_binding<Stack>>>>;

    kodo_factory_t new_sliding_window_decoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        return create_factory<
            runtime_decoder<
            kodo::rlnc::sliding_window_decoder,
            sliding_window_decoder_binding>>(
                finite_field, max_symbols, max_symbol_size);
    }
}

#endif
