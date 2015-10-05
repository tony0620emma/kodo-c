// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>

#include <sak/storage.hpp>

#include <kodo/read_feedback.hpp>

#include <kodo/has_set_systematic_off.hpp>
#include <kodo/is_systematic_on.hpp>
#include <kodo/set_systematic_on.hpp>
#include <kodo/set_systematic_off.hpp>

#include "coder_wrapper.hpp"

namespace kodo
{
    template<class KodoStack, class Base>
    class encoder_wrapper : public coder_wrapper<KodoStack, Base>
    {
    public:

        using Super = coder_wrapper<KodoStack, Base>;

        using coder_type = typename Super::coder_type;

    public:

        encoder_wrapper(const coder_type& coder) :
            Super(coder)
        {
            assert(m_coder);
        }

        virtual bool has_set_systematic_off() const
        {
            return kodo::has_set_systematic_off<KodoStack>::value;
        }

        virtual bool is_systematic_on() const
        {
            return kodo::is_systematic_on(*m_coder);
        }

        virtual void set_systematic_on()
        {
            kodo::set_systematic_on(*m_coder);
        }

        virtual void set_systematic_off()
        {
            kodo::set_systematic_off(*m_coder);
        }

        virtual void read_feedback(uint8_t* feedback)
        {
            kodo::read_feedback(m_coder, feedback);
        }

        virtual uint32_t write_symbol(
            uint8_t* symbol_data, uint8_t* coefficients)
        {
            return m_coder->write_symbol(symbol_data, coefficients);
        }

        virtual uint32_t write_uncoded_symbol(
            uint8_t* symbol_data, uint32_t index)
        {
            return m_coder->write_uncoded_symbol(symbol_data, index);
        }

    protected:

        using Super::m_coder;
    };
}
