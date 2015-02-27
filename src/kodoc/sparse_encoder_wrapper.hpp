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

#include <kodo/trace.hpp>

#include <kodo/has_feedback_size.hpp>
#include <kodo/feedback_size.hpp>

#include "encoder_wrapper.hpp"

namespace kodo
{
    template<class KodoStack, class Base>
    class sparse_encoder_wrapper : public encoder_wrapper<KodoStack, Base>
    {
    public:

        using Super = encoder_wrapper<KodoStack, Base>;

        using coder_type = typename Super::coder_type;

    public:

        sparse_encoder_wrapper(const coder_type& coder) :
            Super(coder)
        {
            assert(m_coder);
        }

        virtual double density() const
        {
            return m_coder->density();
        }

        virtual void set_density(double density)
        {
            m_coder->set_density(density);
        }

    protected:

        using Super::m_coder;
    };
}
