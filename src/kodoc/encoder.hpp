// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "coder.hpp"

extern "C"
{
    /// Base class for an encoder implementation
    struct kodo_encoder : public kodo_coder
    {
    public:

        virtual ~kodo_encoder() {}

        virtual uint32_t encode(uint8_t* data) = 0;

        virtual void set_symbols(
            const uint8_t* data, uint32_t size) = 0;

        virtual void set_symbol(
            uint32_t index, const uint8_t* data, uint32_t size) = 0;

        virtual bool has_systematic_encoder() const = 0;
        virtual bool is_systematic_on() const = 0;
        virtual void set_systematic_on() = 0;
        virtual void set_systematic_off() = 0;
        virtual void read_feedback(uint8_t* feedback) = 0;
    };
}
