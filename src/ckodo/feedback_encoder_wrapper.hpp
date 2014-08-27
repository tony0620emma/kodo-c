#pragma once

#include <cassert>

#include "encoder_wrapper.hpp"

namespace kodo
{
    template<class KodoStack>
    struct feedback_encoder_wrapper : public encoder_wrapper<KodoStack>
    {
        feedback_encoder_wrapper(const typename KodoStack::pointer& encoder)
           : encoder_wrapper<KodoStack>(encoder)
        { }

        using encoder_wrapper<KodoStack>::m_encoder;

        virtual uint32_t feedback_size() const
        {
            return m_encoder->feedback_size();
        }
    };
}
