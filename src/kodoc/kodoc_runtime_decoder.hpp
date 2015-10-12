// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodo/api/api.hpp>
#include <kodo/runtime/empty_binding.hpp>
#include <kodo/runtime/extend_binding.hpp>
#include <kodo/runtime/final.hpp>
#include <kodo/runtime/select_field.hpp>
#include <kodo/runtime/use_shallow_decoder_storage.hpp>
#include <kodo/runtime/use_trace_enabled.hpp>

#include "kodoc_factory_binding.hpp"

namespace kodoc
{
    template<class Stack>
    using decoder_binding =
            kodo::api::storage_binding<
            kodo::api::decoder_binding<
            kodo::api::rank_binding<
            kodo::api::read_payload_binding<
            kodo::api::payload_size_binding<
            kodo::api::final_binding<Stack>>>>>>;

    template
    <
        template <class,class> class Stack,
        template<class> class AdditionalCoderBindings =
            kodo::runtime::empty_binding,
        template<class> class AdditionalCoderFactoryBindings =
            kodo::runtime::empty_binding
    >
    struct kodoc_runtime_decoder :
        kodo::runtime::select_field<
        kodo::runtime::use_shallow_decoder_storage<
        kodo::runtime::use_trace_enabled<
        kodo::runtime::final<Stack,
        kodo::runtime::extend_binding<AdditionalCoderFactoryBindings,
            kodoc_factory_binding>::template type,
        kodo::runtime::extend_binding<AdditionalCoderBindings,
            decoder_binding>::template type>>>>
    { };
}
