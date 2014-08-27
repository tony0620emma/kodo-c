#pragma once

#include <cassert>

#include "encoder_wrapper.hpp"
namespace kodo
{
    template<class KodoStack>
    struct feedback_encoder_wrapper : public encoder_wrapper
    {
        feedback_encoder_wrapperconst (typename KodoStack::pointer& encoder)
          : m_encoder(encoder)
        {
          assert(m_encoder);
        } 

        virtual uint32_t feedback_size() const
        {
            return m_encoder->feedback_size();
        }

        typename KodoStack::pointer m_encoder;
    };
}
