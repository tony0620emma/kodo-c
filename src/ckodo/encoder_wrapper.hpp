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

#include "encoder.hpp"

namespace kodo
{

    template<class KodoStack>
    struct encoder_wrapper : public encoder
    {
        encoder_wrapper(const typename KodoStack::pointer& encoder)
            : m_encoder(encoder)
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

        virtual uint32_t payload_size() const
        {
            return m_encoder->payload_size();
        }

        virtual uint32_t block_size() const
        {
            return m_encoder->block_size();
        }

      //virtual uint32_t feedback_size() const
      //{
      //  return m_encoder->feedback_size();
      //}

        virtual uint32_t symbol_size() const
        {
            return m_encoder->symbol_size();
        }

        virtual uint32_t symbols() const
        {
            return m_encoder->symbols();
        }

        virtual bool symbol_pivot(uint32_t index) const
        {
            return m_encoder->is_symbol_pivot(index);
        }

        virtual uint32_t rank() const
        {
            return m_encoder->rank();
        }

        /*        virtual bool is_systematic() const
        {
            return kodo::is_systematic_encoder(m_encoder);
            }*/

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

        virtual bool has_trace() const
        {
            return kodo::has_trace<KodoStack>::value;
        }

        virtual void trace(kodo_filter_function_t filter_function)
        {
            auto filter = [&filter_function](const std::string& zone)
            {
                return bool(filter_function(zone.c_str()));
            };
            kodo::trace<KodoStack>(m_encoder, std::cout, filter);
        }

      bool has_feedback_size() const;

        typename KodoStack::pointer m_encoder;

    };

    template<class KodoStack>
    bool encoder_wrapper<KodoStack> has_feedback_size() const
    {
        return false;
    }
  
    template<>
    bool encoder_wrapper<sliding_window>has_feedback_size() const 
    {
        return true;
    }
}

