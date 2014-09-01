// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>

#include <sak/storage.hpp>
//#include <kodo/systematic_operations.hpp>
// TEST should be one header file
#include <kodo/is_systematic_on.hpp>
#include <kodo/systematic_encoder.hpp>
#include <kodo/set_systematic_on.hpp>
#include <kodo/set_systematic_off.hpp>

#include <kodo/trace_decode_symbol.hpp>
#include <kodo/trace.hpp>

#include <kodo/has_feedback_size.hpp>
#include <kodo/feedback_size.hpp>

#include "encoder.hpp"
#include "coder_wrapper.hpp"

namespace kodo
{

    template<class KodoStack>
    class encoder_wrapper : public coder_wrapper<KodoStack>, public encoder
    {
    public:
        encoder_wrapper(const typename KodoStack::pointer& encoder):
            coder_wrapper<KodoStack>(encoder),
            m_encoder(encoder)
        {
            assert(m_encoder);
        }

        virtual uint32_t encode(uint8_t *payload)
        {
            return m_encoder->encode(payload);
        }

        virtual void set_symbols(
            const uint8_t* data, uint32_t size)
        {
            auto storage = sak::const_storage(data, size);
            m_encoder->set_symbols(storage);
        }

        virtual void set_symbol(
            uint32_t index, const uint8_t* data, uint32_t size)
        {
            auto storage = sak::const_storage(data, size);
            m_encoder->set_symbol(index, storage);
        }

        /*
        virtual bool is_systematic() const
        {
            return kodo::is_systematic_encoder(m_encoder);
        }
        */

        virtual bool is_systematic_on() const
        {
            return kodo::is_systematic_on(m_encoder);
        }

        virtual void set_systematic_on()
        {
            kodo::set_systematic_on(m_encoder);
        }

        virtual void set_systematic_off()
        {
            kodo::set_systematic_off(m_encoder);
        }
    private:
        typename KodoStack::pointer m_encoder;
    };
}
