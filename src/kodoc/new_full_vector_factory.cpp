// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "kodoc.h"

#include <cstdint>

#include <kodo/api/api.hpp>
#include <kodo/rlnc/full_vector_decoder.hpp>
#include <kodo/rlnc/full_vector_encoder.hpp>
#include <kodo/rlnc/sparse_full_vector_encoder.hpp>

#include "create_factory.hpp"
#include "runtime_decoder.hpp"
#include "runtime_encoder.hpp"

namespace kodoc
{
    kodo_factory_t new_full_vector_encoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        return create_factory<
            runtime_encoder<
            kodo::rlnc::full_vector_encoder,
            kodo::api::systematic_binding>>(
                finite_field, max_symbols, max_symbol_size);
    }

    template<class Stack>
    using sparse_full_vector_encoder_binding =
        kodo::api::sparse_encoder_binding<
        kodo::api::systematic_binding<Stack>>;

    kodo_factory_t new_sparse_full_vector_encoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        return create_factory<
            runtime_encoder<
            kodo::rlnc::sparse_full_vector_encoder,
            sparse_full_vector_encoder_binding>>(
                finite_field, max_symbols, max_symbol_size);
    }

    kodo_factory_t new_full_vector_decoder_factory(int32_t finite_field,
        uint32_t max_symbols, uint32_t max_symbol_size)
    {
        return create_factory<
            runtime_decoder<
            kodo::rlnc::full_vector_decoder,
            kodo::api::write_payload_binding>>(
                finite_field, max_symbols, max_symbol_size);
    }
}
