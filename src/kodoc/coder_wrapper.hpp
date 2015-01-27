// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>

#include <sak/storage.hpp>
#include <kodo/is_partial_complete.hpp>
#include <kodo/has_partial_decoding_tracker.hpp>

#include <kodo/trace_decode_symbol.hpp>
#include <kodo/symbol_decoding_status_tracker.hpp>
#include <kodo/trace.hpp>

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

        virtual bool symbol_pivot(uint32_t index) const
        {
            return m_coder->is_symbol_pivot(index);
        }

        virtual void set_symbols(uint8_t* data, uint32_t size)
        {
            sak::mutable_storage storage = sak::storage(data, size);
            m_coder->set_symbols(storage);
        }

        virtual void set_symbol(
            uint32_t index, uint8_t* data, uint32_t size)
        {
            sak::mutable_storage storage = sak::storage(data, size);
            m_coder->set_symbol(index, storage);
        }

        virtual bool has_trace() const
        {
            return kodo::has_trace<KodoStack>::value;
        }

        virtual void trace(kodo_trace_callback_t trace_callback)
        {
            if (!kodo::has_trace<KodoStack>::value)
                return;

            if (trace_callback)
            {
                auto callback = [trace_callback](const std::string& zone,
                                                 const std::string& data)
                {
                    trace_callback(zone.c_str(), data.c_str());
                };

                kodo::trace<KodoStack>(*m_coder, callback);
            }
            else
            {
                kodo::trace<KodoStack>(*m_coder);
            }
        }

        virtual bool has_feedback_size() const
        {
            return kodo::has_feedback_size<KodoStack>::value;
        }

        virtual uint32_t feedback_size() const
        {
            return kodo::feedback_size(m_coder);
        }

        virtual uint32_t write_payload(uint8_t *payload)
        {
            assert(payload);
            assert(m_coder);

            return m_coder->write_payload(payload);
        }

    protected:

        coder_type m_coder;
    };
}
