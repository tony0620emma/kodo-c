#include "ckodo.h"
#include "encoder_factory_wrapper.hpp"
#include "decoder_factory_wrapper.hpp"

#include <kodo/rlnc/full_vector_codes.hpp>


// Initialize the type constants
// Typdefs for the encoder/decoder type we wish to use
typedef kodo::full_rlnc_encoder<fifi::binary> full_rlnc_encoder;
typedef kodo::full_rlnc_decoder<fifi::binary> full_rlnc_decoder;

typedef kodo::full_rlnc_encoder<fifi::binary8> full_rlnc_encoder8;
typedef kodo::full_rlnc_decoder<fifi::binary8> full_rlnc_decoder8;

typedef kodo::full_rlnc_encoder<fifi::binary16> full_rlnc_encoder16;
typedef kodo::full_rlnc_decoder<fifi::binary16> full_rlnc_decoder16;

const size_t kodo_binary = typeid(fifi::binary).hash_code();
const size_t kodo_binary8 = typeid(fifi::binary8).hash_code();
const size_t kodo_binary16 = typeid(fifi::binary16).hash_code();

const size_t kodo_full_rlnc =
    typeid(full_rlnc_encoder).hash_code();

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

    // The code type was unknown
    assert(factory);

    return factory;
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


void* kodo_new_encoder(void* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->build();
}

void* kodo_new_decoder(void* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->build();
}

void kodo_delete_encoder(void* encoder)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    delete the_encoder;
}

void kodo_delete_decoder(void* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    delete the_decoder;
}

uint32_t kodo_max_symbols(void* factory)
{
    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->max_symbols();
}

uint32_t kodo_max_symbol_size(void* factory)
{
    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->max_symbol_size();
}

uint32_t kodo_max_block_size(void* factory)
{
    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->max_block_size();
}

uint32_t kodo_max_payload_size(void* factory)
{
    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->max_payload_size();
}

void kodo_set_symbols(kodo_factory_t* factory, uint32_t symbols)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    the_factory->set_symbols(symbols);
}

void kodo_set_symbol_size(kodo_factory_t* factory, uint32_t symbol_size)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    the_factory->set_symbol_size(symbol_size);
}




uint32_t kodo_block_size(void* coder)
{
    kodo::coder* the_coder = (kodo::coder*) coder;
    return the_coder->block_size();
}

uint32_t kodo_payload_size(void* coder)
{
    kodo::coder* the_coder = (kodo::coder*) coder;
    return the_coder->payload_size();
}

uint32_t kodo_encode(void* encoder, uint8_t* data)
{
    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    return the_encoder->encode(data);
}

void kodo_set_symbols(void* encoder, const uint8_t* data, uint32_t size)
{
    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    the_encoder->set_symbols(data, size);
}

void kodo_set_symbol(void* encoder, uint32_t index, const uint8_t* data, uint32_t size)
{
    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    the_encoder->set_symbol(index, data, size);
}

void kodo_decode(void* decoder, uint8_t *data)
{
    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    the_decoder->decode(data);
}

uint8_t kodo_is_complete(void* decoder)
{
    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return (uint8_t)the_decoder->is_complete();
}

uint32_t kodo_rank(void* decoder)
{
    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return the_decoder->rank();
}

void kodo_copy_symbols(void* decoder, uint8_t* data, uint32_t size)
{
    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    the_decoder->copy_symbols(data, size);
}





