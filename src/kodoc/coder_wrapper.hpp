// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>
#include <string>

#include <sak/storage.hpp>

#include <kodo/has_feedback_size.hpp>
#include <kodo/feedback_size.hpp>
#include <kodo/has_set_trace_callback.hpp>
#include <kodo/set_trace_callback.hpp>
#include <kodo/has_set_trace_stdout.hpp>
#include <kodo/set_trace_stdout.hpp>
#include <kodo/has_set_trace_off.hpp>
#include <kodo/set_trace_off.hpp>
#include <kodo/has_write_payload.hpp>
#include <kodo/write_payload.hpp>

namespace kodo
{
    template<class KodoStack, class Base>
    class coder_wrapper : public Base
    {
    public:

        using coder_type = typename KodoStack::factory::pointer;

    public:

        coder_wrapper(const coder_type& coder) :
            m_coder(coder)
        {
            assert(m_coder);
        }

        virtual uint32_t block_size() const
        {
            return m_coder->block_size();
        }

        virtual uint32_t payload_size() const
        {
            return m_coder->payload_size();
        }

        virtual uint32_t rank() const
        {
            return m_coder->rank();
        }

        virtual uint32_t symbol_size() const
        {
            return m_coder->symbol_size();
        }

        virtual uint32_t symbols() const
        {
            return m_coder->symbols();
        }

        virtual bool is_symbol_pivot(uint32_t index) const
        {
            return m_coder->is_symbol_pivot(index);
        }

        virtual bool has_set_trace_callback() const
        {
            return kodo::has_set_trace_callback<KodoStack>::value;
        }

        virtual bool has_set_trace_stdout() const
        {
            return kodo::has_set_trace_stdout<KodoStack>::value;
        }

        virtual bool has_set_trace_off() const
        {
            return kodo::has_set_trace_off<KodoStack>::value;
        }

        virtual void set_trace_callback(kodo_trace_callback_t trace_callback,
            void* context)
        {
            assert(trace_callback);
            auto callback = [trace_callback, context](const std::string& zone,
                                             const std::string& data)
            {
                trace_callback(zone.c_str(), data.c_str(), context);
            };

            kodo::set_trace_callback<KodoStack>(*m_coder, callback);
        }

        virtual void set_trace_stdout()
        {
            kodo::set_trace_stdout<KodoStack>(*m_coder);
        }

        virtual void set_trace_off()
        {
            kodo::set_trace_off<KodoStack>(*m_coder);
        }

        virtual bool has_feedback_size() const
        {
            return kodo::has_feedback_size<KodoStack>::value;
        }

        virtual uint32_t feedback_size() const
        {
            return kodo::feedback_size(m_coder);
        }

        virtual bool has_write_payload() const
        {
            return kodo::has_write_payload<KodoStack>::value;
        }

        virtual uint32_t write_payload(uint8_t* payload)
        {
            assert(payload);
            return kodo::write_payload(m_coder, payload);
        }

    protected:

        coder_type m_coder;
    };
}
