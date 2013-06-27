#include "ckodo.h"

#include <kodo/rlnc/full_vector_codes.hpp>




/// Initialize the type constants
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



struct kodo_encoder_
{
    virtual uint32_t encode(uint8_t* payload) = 0;
};



struct kodo_decoder_
{
    virtual void decode(uint8_t* payload) = 0;
};

template<class KodoEncoder>
struct kodo_encoder_wrapper : public kodo_encoder_
{
    kodo_encoder_wrapper(const typename KodoEncoder::pointer& encoder)
        : m_encoder(encoder)
    {
        assert(m_encoder);
    }

    virtual uint32_t encode(uint8_t* payload)
    {
        assert(payload);
        assert(m_encoder);

        return m_encoder->encode(payload);
    }

    typename KodoEncoder::pointer m_encoder;
};


template<class KodoDecoder>
struct kodo_decoder_wrapper : public kodo_decoder_
{
    kodo_decoder_wrapper(const typename KodoDecoder::pointer& decoder)
        : m_decoder(decoder)
    {
        assert(m_decoder);
    }

    virtual void decode(uint8_t* payload)
    {
        assert(payload);
        assert(m_decoder);

        m_decoder->decode(payload);
    }

    typename KodoDecoder::pointer m_decoder;
};

struct kodo_encoder_factory_
{
    virtual kodo_encoder_* build() = 0;

    virtual uint32_t max_symbols() const = 0;
    virtual uint32_t max_symbol_size() const = 0;
    virtual uint32_t max_block_size() const = 0;
    virtual uint32_t max_payload_size() const = 0;
};


struct kodo_decoder_factory_
{
    virtual kodo_decoder_* build() = 0;

    virtual uint32_t max_symbols() const = 0;
    virtual uint32_t max_symbol_size() const = 0;
    virtual uint32_t max_block_size() const = 0;
    virtual uint32_t max_payload_size() const = 0;
};

template<class KodoEncoder>
struct kodo_encoder_factory_wrapper : public kodo_encoder_factory_
{
    kodo_encoder_factory_wrapper(uint32_t max_symbols,
                                 uint32_t max_symbol_size)
        : m_factory(max_symbols, max_symbol_size)
    {

    }

    kodo_encoder_* build()
    {
        auto encoder = m_factory.build();

        kodo_encoder_* base =
            new kodo_encoder_wrapper<KodoEncoder>(encoder);

        return base;
    }

    virtual uint32_t max_symbols() const
    {
        return m_factory.max_symbols();
    }

    virtual uint32_t max_symbol_size() const
    {
        return m_factory.max_symbol_size();
    }

    virtual uint32_t max_block_size() const
    {
        return m_factory.max_block_size();
    }

    virtual uint32_t max_payload_size() const
    {
        return m_factory.max_payload_size();
    }

    typename KodoEncoder::factory m_factory;
};


template<class KodoDecoder>
struct kodo_decoder_factory_wrapper : public kodo_decoder_factory_
{
    kodo_decoder_factory_wrapper(uint32_t max_symbols,
                                 uint32_t max_symbol_size)
        : m_factory(max_symbols, max_symbol_size)
    {

    }

    kodo_decoder_* build()
    {
        auto decoder = m_factory.build();

        kodo_decoder_* base =
            new kodo_decoder_wrapper<KodoDecoder>(decoder);

        return base;
    }

    virtual uint32_t max_symbols() const
    {
        return m_factory.max_symbols();
    }

    virtual uint32_t max_symbol_size() const
    {
        return m_factory.max_symbol_size();
    }

    virtual uint32_t max_block_size() const
    {
        return m_factory.max_block_size();
    }

    virtual uint32_t max_payload_size() const
    {
        return m_factory.max_payload_size();
    }


    typename KodoDecoder::factory m_factory;
};







// template<class Field>
// struct kodo_full_rlnc_encoder : public kodo_encoder_
// {
// };




//------------------------------------------------------------------
// FACTORY API
//------------------------------------------------------------------

kodo_encoder_factory*
kodo_new_encoder_factory(
    size_t code_type, size_t field_type,
    uint32_t max_symbols, uint32_t max_symbol_size)
{
    kodo_encoder_factory_ *factory = 0;

    if(code_type == kodo_full_rlnc)
    {
        if(field_type == kodo_binary)
        {
            factory = new kodo_encoder_factory_wrapper<
                full_rlnc_encoder>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary8)
        {
            factory = new kodo_encoder_factory_wrapper<
                full_rlnc_encoder8>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary16)
        {
            factory = new kodo_encoder_factory_wrapper<
                full_rlnc_encoder16>(max_symbols, max_symbol_size);
        }

    }

    assert(factory);

    return factory;
}


kodo_decoder_factory*
kodo_new_decoder_factory(
    size_t code_type, size_t field_type,
    uint32_t max_symbols, uint32_t max_symbol_size)
{
    kodo_decoder_factory_ *factory = 0;

    if(code_type == kodo_full_rlnc)
    {
        if(field_type == kodo_binary)
        {
            factory = new kodo_decoder_factory_wrapper<
                full_rlnc_decoder>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary8)
        {
            factory = new kodo_decoder_factory_wrapper<
                full_rlnc_decoder8>(max_symbols, max_symbol_size);
        }
        if(field_type == kodo_binary16)
        {
            factory = new kodo_decoder_factory_wrapper<
                full_rlnc_decoder16>(max_symbols, max_symbol_size);
        }


    }

    assert(factory);

    return factory;
}

kodo_encoder* kodo_new_encoder(kodo_encoder_factory* factory)
{
    assert(factory);

    kodo_encoder *encoder = factory->build();
    return encoder;
}

kodo_decoder* kodo_new_decoder(kodo_decoder_factory* factory)
{
    assert(factory);

    kodo_decoder *decoder = factory->build();
    return decoder;
}

void kodo_delete_encoder_factory(kodo_encoder_factory* factory)
{
    assert(factory);
    delete factory;
}

void kodo_delete_decoder_factory(kodo_decoder_factory* factory)
{
    assert(factory);
    delete factory;
}

void kodo_delete_encoder(kodo_encoder* encoder)
{
    assert(encoder);
    delete encoder;
}

void kodo_delete_decoder(kodo_decoder* decoder)
{
    assert(decoder);
    delete decoder;
}




