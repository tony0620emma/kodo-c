// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "ckodo.h"
#include "encoder_factory_wrapper.hpp"
#include "decoder_factory_wrapper.hpp"

#include <kodo/rlnc/full_vector_codes.hpp>
#include <kodo/rlnc/on_the_fly_codes.hpp>

// Initialize the type constants
// Typdefs for the encoder/decoder type we wish to use
typedef kodo::full_rlnc_encoder<fifi::binary> full_rlnc_encoder;
typedef kodo::full_rlnc_decoder<fifi::binary> full_rlnc_decoder;
typedef kodo::debug_full_rlnc_decoder<fifi::binary> debug_full_rlnc_decoder;

typedef kodo::full_rlnc_encoder<fifi::binary8> full_rlnc_encoder8;
typedef kodo::full_rlnc_decoder<fifi::binary8> full_rlnc_decoder8;
typedef kodo::debug_full_rlnc_decoder<fifi::binary8> debug_full_rlnc_decoder8;

typedef kodo::full_rlnc_encoder<fifi::binary16> full_rlnc_encoder16;
typedef kodo::full_rlnc_decoder<fifi::binary16> full_rlnc_decoder16;
typedef kodo::debug_full_rlnc_decoder<fifi::binary16>
    debug_full_rlnc_decoder16;

// Typedefs for the on-the-fly coders
typedef kodo::on_the_fly_encoder<fifi::binary> on_the_fly_encoder;
typedef kodo::on_the_fly_decoder<fifi::binary> on_the_fly_decoder;
typedef kodo::debug_on_the_fly_decoder<fifi::binary> debug_on_the_fly_decoder;

typedef kodo::on_the_fly_encoder<fifi::binary8> on_the_fly_encoder8;
typedef kodo::on_the_fly_decoder<fifi::binary8> on_the_fly_decoder8;
typedef kodo::debug_on_the_fly_decoder<fifi::binary8>
    debug_on_the_fly_decoder8;

typedef kodo::on_the_fly_encoder<fifi::binary16> on_the_fly_encoder16;
typedef kodo::on_the_fly_decoder<fifi::binary16> on_the_fly_decoder16;
typedef kodo::debug_on_the_fly_decoder<fifi::binary16>
    debug_on_the_fly_decoder16;


const size_t kodo_binary = typeid(fifi::binary).hash_code();
const size_t kodo_binary8 = typeid(fifi::binary8).hash_code();
const size_t kodo_binary16 = typeid(fifi::binary16).hash_code();

const size_t kodo_full_rlnc =
    typeid(full_rlnc_encoder).hash_code();

const size_t kodo_debug_full_rlnc =
    typeid(debug_full_rlnc_decoder).hash_code();

const size_t kodo_on_the_fly =
    typeid(on_the_fly_encoder).hash_code();

const size_t kodo_debug_on_the_fly =
    typeid(debug_on_the_fly_decoder).hash_code();


//------------------------------------------------------------------
// FACTORY API
//------------------------------------------------------------------

kodo_factory_t*
kodo_new_encoder_factory(size_t code_type, size_t field_type,
                         uint32_t max_symbols, uint32_t max_symbol_size)
{
    kodo::factory *factory = 0;

    if(code_type == kodo_full_rlnc)
    {
        if(field_type == kodo_binary)
        {
            factory = new kodo::encoder_factory_wrapper<
                full_rlnc_encoder>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary8)
        {
            factory = new kodo::encoder_factory_wrapper<
                full_rlnc_encoder8>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary16)
        {
            factory = new kodo::encoder_factory_wrapper<
                full_rlnc_encoder16>(max_symbols, max_symbol_size);
        }

        // The field type was unknown
        assert(factory);

    }

    // We have not added any debug layers on the encoder yet, but we
    // just prepare here
    if(code_type == kodo_debug_full_rlnc)
    {
        if(field_type == kodo_binary)
        {
            factory = new kodo::encoder_factory_wrapper<
                full_rlnc_encoder>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary8)
        {
            factory = new kodo::encoder_factory_wrapper<
                full_rlnc_encoder8>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary16)
        {
            factory = new kodo::encoder_factory_wrapper<
                full_rlnc_encoder16>(max_symbols, max_symbol_size);
        }

        // The field type was unknown
        assert(factory);

    }

    if(code_type == kodo_on_the_fly)
    {
        if(field_type == kodo_binary)
        {
            factory = new kodo::encoder_factory_wrapper<
                on_the_fly_encoder>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary8)
        {
            factory = new kodo::encoder_factory_wrapper<
                on_the_fly_encoder8>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary16)
        {
            factory = new kodo::encoder_factory_wrapper<
                on_the_fly_encoder16>(max_symbols, max_symbol_size);
        }

        // The field type was unknown
        assert(factory);

    }

    if(code_type == kodo_debug_on_the_fly)
    {
        if(field_type == kodo_binary)
        {
            factory = new kodo::encoder_factory_wrapper<
                on_the_fly_encoder>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary8)
        {
            factory = new kodo::encoder_factory_wrapper<
                on_the_fly_encoder8>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary16)
        {
            factory = new kodo::encoder_factory_wrapper<
                on_the_fly_encoder16>(max_symbols, max_symbol_size);
        }

        // The field type was unknown
        assert(factory);

    }


    // The code type was unknown
    assert(factory);

    return (kodo_factory_t*)factory;
}


kodo_factory_t*
kodo_new_decoder_factory(size_t code_type, size_t field_type,
                         uint32_t max_symbols, uint32_t max_symbol_size)
{
    kodo::factory *factory = 0;

    if(code_type == kodo_full_rlnc)
    {
        if(field_type == kodo_binary)
        {
            factory = new kodo::decoder_factory_wrapper<
                full_rlnc_decoder>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary8)
        {
            factory = new kodo::decoder_factory_wrapper<
                full_rlnc_decoder8>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary16)
        {
            factory = new kodo::decoder_factory_wrapper<
                full_rlnc_decoder16>(max_symbols, max_symbol_size);
        }

        // The field type was unknown
        assert(factory);

    }

    if(code_type == kodo_debug_full_rlnc)
    {
        if(field_type == kodo_binary)
        {
            factory = new kodo::decoder_factory_wrapper<
                debug_full_rlnc_decoder>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary8)
        {
            factory = new kodo::decoder_factory_wrapper<
                debug_full_rlnc_decoder8>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary16)
        {
            factory = new kodo::decoder_factory_wrapper<
                debug_full_rlnc_decoder16>(max_symbols, max_symbol_size);
        }

        // The field type was unknown
        assert(factory);

    }

    if(code_type == kodo_on_the_fly)
    {
        if(field_type == kodo_binary)
        {
            factory = new kodo::decoder_factory_wrapper<
                on_the_fly_decoder>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary8)
        {
            factory = new kodo::decoder_factory_wrapper<
                on_the_fly_decoder8>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary16)
        {
            factory = new kodo::decoder_factory_wrapper<
                on_the_fly_decoder16>(max_symbols, max_symbol_size);
        }

        // The field type was unknown
        assert(factory);

    }

    if(code_type == kodo_debug_on_the_fly)
    {
        if(field_type == kodo_binary)
        {
            factory = new kodo::decoder_factory_wrapper<
                debug_on_the_fly_decoder>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary8)
        {
            factory = new kodo::decoder_factory_wrapper<
                debug_on_the_fly_decoder8>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary16)
        {
            factory = new kodo::decoder_factory_wrapper<
                debug_on_the_fly_decoder16>(max_symbols, max_symbol_size);
        }

        // The field type was unknown
        assert(factory);

    }

    // The code type was unknown
    assert(factory);

    return (kodo_factory_t*)factory;
}

void kodo_delete_encoder_factory(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    delete the_factory;
}

void kodo_delete_decoder_factory(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    delete the_factory;
}


uint32_t kodo_factory_max_symbols(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->max_symbols();
}

uint32_t kodo_factory_max_symbol_size(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->max_symbol_size();
}

uint32_t kodo_factory_max_block_size(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->max_block_size();
}

uint32_t kodo_factory_max_payload_size(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->max_payload_size();
}

void kodo_factory_set_symbols(kodo_factory_t* factory, uint32_t symbols)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    the_factory->set_symbols(symbols);
}

void kodo_factory_set_symbol_size(kodo_factory_t* factory,
                                  uint32_t symbol_size)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    the_factory->set_symbol_size(symbol_size);
}


kodo_coder_t* kodo_factory_new_encoder(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    void* encoder = the_factory->build();
    return (kodo_coder_t*) encoder;
}

kodo_coder_t* kodo_factory_new_decoder(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    void* decoder = the_factory->build();
    return (kodo_coder_t*) decoder;
}

void kodo_delete_encoder(kodo_coder_t* encoder)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    delete the_encoder;
}

void kodo_delete_decoder(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    delete the_decoder;
}

//------------------------------------------------------------------
// PAYLOAD API
//------------------------------------------------------------------

uint32_t kodo_payload_size(kodo_coder_t* coder)
{
    assert(coder);

    kodo::coder* the_coder = (kodo::coder*) coder;
    return the_coder->payload_size();
}

void kodo_decode(kodo_coder_t* decoder, uint8_t* payload)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    the_decoder->decode(payload);
}

uint32_t kodo_recode(kodo_coder_t* decoder, uint8_t* payload)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return the_decoder->recode(payload);
}

uint32_t kodo_encode(kodo_coder_t* encoder, uint8_t* payload)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    return the_encoder->encode(payload);
}

//------------------------------------------------------------------
// SYMBOL STORAGE API
//------------------------------------------------------------------

uint32_t kodo_block_size(kodo_coder_t* coder)
{
    assert(coder);

    kodo::coder* the_coder = (kodo::coder*) coder;
    return the_coder->block_size();
}


void kodo_set_symbols(kodo_coder_t* encoder, const uint8_t* data,
                      uint32_t size)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    the_encoder->set_symbols(data, size);
}

void kodo_set_symbol(kodo_coder_t* encoder, uint32_t index,
                     const uint8_t* data, uint32_t size)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    the_encoder->set_symbol(index, data, size);
}

void kodo_copy_symbols(kodo_coder_t* decoder, uint8_t* data, uint32_t size)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    the_decoder->copy_symbols(data, size);
}

void kodo_copy_symbol(kodo_coder_t* decoder, uint32_t index,
                      uint8_t* data, uint32_t size)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    the_decoder->copy_symbol(index, data, size);

}


uint32_t kodo_symbol_size(kodo_coder_t* coder)
{
    assert(coder);

    kodo::coder* the_coder = (kodo::coder*) coder;
    return the_coder->symbol_size();
}

uint32_t kodo_symbols(kodo_coder_t* coder)
{
    assert(coder);

    kodo::coder* the_coder = (kodo::coder*) coder;
    return the_coder->symbols();
}


//------------------------------------------------------------------
// CODEC API
//------------------------------------------------------------------

uint8_t kodo_is_complete(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return (uint8_t)the_decoder->is_complete();
}

uint8_t kodo_is_partial_complete(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return (uint8_t)the_decoder->is_partial_complete();

}

uint32_t kodo_rank(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return the_decoder->rank();
}

uint8_t kodo_symbol_pivot(kodo_coder_t* coder, uint32_t index)
{
    assert(coder);

    kodo::coder* the_coder = (kodo::coder*) coder;
    return the_coder->symbol_pivot(index);
}

uint8_t kodo_is_symbol_decoded(kodo_coder_t* decoder, uint32_t index)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return the_decoder->is_symbol_decoded(index);
}

//------------------------------------------------------------------
// GENERIC API
//------------------------------------------------------------------

uint8_t kodo_has_partial_decoding_tracker(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return (uint8_t)the_decoder->has_partial_decoding_tracker();
}

uint8_t kodo_is_systematic(kodo_coder_t* encoder)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    return (uint8_t)the_encoder->is_systematic();
}

uint8_t kodo_is_systematic_on(kodo_coder_t* encoder)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    return (uint8_t)the_encoder->is_systematic_on();
}

void kodo_set_systematic_on(kodo_coder_t* encoder)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    the_encoder->set_systematic_on();
}

void kodo_set_systematic_off(kodo_coder_t* encoder)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    the_encoder->set_systematic_off();
}

//------------------------------------------------------------------
// DEBUG API
//------------------------------------------------------------------

uint8_t kodo_has_print_decoder_state(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return (uint8_t)the_decoder->has_print_decoder_state();
}

void kodo_print_decoder_state(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    the_decoder->print_decoder_state();
}

uint8_t kodo_has_print_cached_symbol_coefficients(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return (uint8_t)the_decoder->has_print_cached_symbol_coefficients();
}

void kodo_print_cached_symbol_coefficients(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    the_decoder->print_cached_symbol_coefficients();
}

uint8_t kodo_has_print_cached_symbol_data(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return (uint8_t)the_decoder->has_print_cached_symbol_data();
}

void kodo_print_cached_symbol_data(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    the_decoder->print_cached_symbol_data();
}




