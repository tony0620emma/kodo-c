// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "coder.hpp"

namespace kodo
{
    struct decoder : public coder
    {
        virtual uint32_t recode(uint8_t *) = 0;
        virtual void decode(uint8_t *) = 0;
        virtual bool is_complete() const = 0;

        virtual void copy_symbols(uint8_t* data, uint32_t size) const = 0;

        virtual void copy_symbol(uint32_t index, uint8_t* data,
                                 uint32_t size) const = 0;

        virtual bool has_partial_decoding_tracker() const = 0;
        virtual bool is_partial_complete() const = 0;
        virtual bool is_symbol_uncoded(uint32_t) const = 0;

        // Debugging support

/* virtual bool has_print_decoder_state() const = 0;
        

        virtual bool has_print_cached_symbol_coefficients() const = 0;
        virtual void print_cached_symbol_coefficients() const = 0;
        virtual void print_decoder_state() const = 0;        
        virtual bool has_print_cached_symbol_data() const = 0;
        virtual void print_cached_symbol_data() const = 0;
        */
        virtual ~decoder(){}
    };
}


