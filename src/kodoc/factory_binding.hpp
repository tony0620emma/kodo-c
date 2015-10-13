// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodo/api/api.hpp>

namespace kodoc
{
    template<class Factory>
    using factory_binding =
        kodo::api::storage_block_info_binding<
        kodo::api::max_payload_size_binding<
        kodo::api::final_binding<Factory>>>;
}
