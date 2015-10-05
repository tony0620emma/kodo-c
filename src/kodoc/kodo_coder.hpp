// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "kodoc.h"

extern "C"
{
    /// Represents the common interface of encoders and decoders.
    struct kodo_coder
    {
        virtual ~kodo_coder() {}

        virtual uint32_t block_size() const = 0;
        virtual uint32_t payload_size() const = 0;
        virtual uint32_t rank() const = 0;
        virtual uint32_t symbol_size() const = 0;
        virtual uint32_t symbols() const = 0;
        virtual bool is_symbol_pivot(uint32_t index) const = 0;

        virtual bool has_set_trace_stdout() const = 0;
        virtual bool has_set_trace_callback() const = 0;
        virtual bool has_set_trace_off() const = 0;

        virtual void set_trace_stdout() = 0;
        virtual void set_trace_callback(kodo_trace_callback_t callback,
            void* context) = 0;
        virtual void set_trace_off() = 0;

        virtual bool has_feedback_size() const = 0;
        virtual uint32_t feedback_size() const = 0;

        virtual bool has_write_payload() const = 0;
        virtual uint32_t write_payload(uint8_t* data) = 0;
    };
}
