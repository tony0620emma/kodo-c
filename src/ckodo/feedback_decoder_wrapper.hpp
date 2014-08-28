#pragma once

#include <cassert>

#include "decoder_wrapper.hpp"

namespace kodo
{
    template<class KodoStack>
    struct feedback_decoder_wrapper : public decoder_wrapper<KodoStack>
    {
        feedback_decoder_wrapper(const typename KodoStack::pointer& decoder)
           : decoder_wrapper<KodoStack>(decoder)
        { }

        using decoder_wrapper<KodoStack>::m_decoder;

        virtual uint32_t feedback_size() const
        {
            return m_decoder->feedback_size();
        }

        virtual void write_feedback()
        {
        
        }
    };
}
