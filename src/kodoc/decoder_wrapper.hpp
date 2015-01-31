// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>

#include <sak/storage.hpp>

#include <kodo/write_feedback.hpp>

#include <kodo/is_partial_complete.hpp>
#include <kodo/has_partial_decoding_tracker.hpp>

#include <kodo/trace_linear_block_decoder.hpp>
#include <kodo/symbol_decoding_status_tracker.hpp>
#include <kodo/trace.hpp>

#include "coder_wrapper.hpp"
#include "decoder.hpp"

namespace kodo
{
    template<class KodoStack>
    class decoder_wrapper : public coder_wrapper<KodoStack, kodo_decoder>
    {
    public:

        using Super = coder_wrapper<KodoStack, kodo_decoder>;

        using coder_type = typename Super::coder_type;

    public:

        decoder_wrapper(const coder_type& coder) :
            Super(coder)
        {
            assert(m_coder);
        }

        virtual void read_payload(uint8_t *payload)
        {
            assert(payload);
            assert(m_coder);

            m_coder->read_payload(payload);
        }

        virtual bool is_complete() const
        {
            assert(m_coder);
            return m_coder->is_complete();
        }

        virtual void copy_symbols(uint8_t* data, uint32_t size) const
        {
            auto storage = sak::mutable_storage(data, size);
            m_coder->copy_symbols(storage);
        }

        virtual void copy_symbol(uint32_t index, uint8_t* data,
                                 uint32_t size) const
        {
            auto storage = sak::mutable_storage(data, size);
            m_coder->copy_symbol(index, storage);
        }

        virtual bool has_partial_decoding_tracker() const
        {
            return kodo::has_partial_decoding_tracker<KodoStack>::value;
        }

        virtual bool is_partial_complete() const
        {
            return kodo::is_partial_complete(m_coder);
        }

        virtual bool is_symbol_uncoded(uint32_t index) const
        {
            return m_coder->is_symbol_uncoded(index);
        }

        virtual uint32_t symbols_uncoded() const
        {
            return m_coder->symbols_uncoded();
        }

        virtual uint32_t symbols_seen() const
        {
            return m_coder->symbols_seen();
        }

        virtual void write_feedback(uint8_t* feedback)
        {
            kodo::write_feedback(m_coder, feedback);
        }

        virtual void read_symbol(
            uint8_t* symbol_data, uint8_t* coefficients)
        {
            m_coder->read_symbol(symbol_data, coefficients);
        }

        virtual void read_uncoded_symbol(
            uint8_t* symbol_data, uint32_t index)
        {
            m_coder->read_uncoded_symbol(symbol_data, index);
        }

    protected:

        using Super::m_coder;
    };
}
