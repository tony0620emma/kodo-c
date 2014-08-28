// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>

#include <sak/storage.hpp>
#include <kodo/is_partial_complete.hpp>
#include <kodo/has_partial_decoding_tracker.hpp>

#include <kodo/trace_decode_symbol.hpp>
#include <kodo/trace_linear_block_decoder.hpp>
#include <kodo/symbol_decoding_status_tracker.hpp>
#include <kodo/trace.hpp>

#include "decoder.hpp"


namespace kodo
{

    template<class KodoStack>
    struct decoder_wrapper : public decoder
    {
        decoder_wrapper(const typename KodoStack::pointer& decoder)
            : m_decoder(decoder)
        {
            assert(m_decoder);
        }

        virtual uint32_t recode(uint8_t *payload)
        {
            assert(payload);
            assert(m_decoder);

            return m_decoder->recode(payload);
        }

        virtual void decode(uint8_t *payload)
        {
            assert(payload);
            assert(m_decoder);

            m_decoder->decode(payload);
        }

        virtual bool is_complete() const
        {
            assert(m_decoder);
            return m_decoder->is_complete();
        }

        virtual uint32_t rank() const
        {
            assert(m_decoder);
            return m_decoder->rank();
        }

        virtual uint32_t payload_size() const
        {
            return m_decoder->payload_size();
        }

        virtual uint32_t block_size() const
        {
            return m_decoder->block_size();
        }

      //virtual uint32_t feedback_size() const
      //{
      //  return m_decoder->feedback_size();
      //}

        virtual uint32_t symbol_size() const
        {
            return m_decoder->symbol_size();
        }

        virtual uint32_t symbols() const
        {
            return m_decoder->symbols();
        }

        virtual bool symbol_pivot(uint32_t index) const
        {
            return m_decoder->is_symbol_pivot(index);
        }

        virtual void copy_symbols(uint8_t* data, uint32_t size) const
        {
            auto storage = sak::mutable_storage(data, size);
            m_decoder->copy_symbols(storage);
        }

        virtual void copy_symbol(uint32_t index, uint8_t* data,
                                 uint32_t size) const
        {
            auto storage = sak::mutable_storage(data, size);
            m_decoder->copy_symbol(index, storage);
        }

        virtual bool has_partial_decoding_tracker() const
        {
            return kodo::has_partial_decoding_tracker<KodoStack>::value;
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
            kodo::trace<KodoStack>(m_decoder, std::cout, filter);
        }

        virtual bool is_partial_complete() const
        {
            return kodo::is_partial_complete(m_decoder);
        }

        virtual bool is_symbol_uncoded(uint32_t index) const
        {
            return m_decoder->is_symbol_uncoded(index);
        }

        virtual uint32_t symbols_uncoded() const
        {
            return m_decoder->symbols_uncoded();
	}

        virtual uint32_t symbols_seen() const
        {
            return m_decoder->symbols_seen();
        }
        bool has_feedback_size() const;

        typename KodoStack::pointer m_decoder;



    };

    template<class KodoStack>
    bool decoder_wrapper<KodoStack> has_feedback_size() const;
    {
        return false;
    }
  
    template<>
    bool decoder_wrapper<sliding_window>has_feedback_size() const 
    {
        return true;
    }

}

