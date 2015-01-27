// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>

#include <sak/storage.hpp>

#include <kodo/read_feedback.hpp>

#include <kodo/has_systematic_encoder.hpp>
#include <kodo/is_systematic_on.hpp>
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
    class encoder_wrapper : public coder_wrapper<KodoStack, kodo_encoder>
    {
    public:

        using Super = coder_wrapper<KodoStack, kodo_encoder>;

        using coder_type = typename Super::coder_type;

    public:

        encoder_wrapper(const coder_type& coder) :
            Super(coder)
        {
            assert(m_coder);
        }

        virtual bool has_systematic_encoder() const
        {
            return kodo::has_systematic_encoder<KodoStack>::value;
        }

        virtual bool is_systematic_on() const
        {
            return kodo::is_systematic_on(m_coder);
        }

        virtual void set_systematic_on()
        {
            kodo::set_systematic_on(m_coder);
        }

        virtual void set_systematic_off()
        {
            kodo::set_systematic_off(m_coder);
        }

        virtual void read_feedback(uint8_t* feedback)
        {
            kodo::read_feedback(m_coder, feedback);
        }

    protected:

        using Super::m_coder;
    };
}
