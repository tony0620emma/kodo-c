// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "encoder.hpp"

extern "C"
{
    /// Interface class for a sparse encoder implementation
    struct kodo_sparse_encoder : public kodo_encoder
    {
    public:

        virtual ~kodo_sparse_encoder() {}

        virtual double density() const = 0;
        virtual void set_density(double density) = 0;
    };
}
