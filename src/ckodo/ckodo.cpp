#include "ckodo.h"

#include <kodo/rlnc/full_vector_codes.hpp>

struct kodo_codec_
{
    kodo_codec_(uint32_t max_symbols, uint32_t max_symbol_size)
        : m_encoder_factory(max_symbols, max_symbol_size),
          m_decoder_factory(max_symbols, max_symbol_size)
    {
    }

    // Typdefs for the encoder/decoder type we wish to use
    typedef kodo::full_rlnc_encoder<fifi::binary8> rlnc_encoder;
    typedef kodo::full_rlnc_decoder<fifi::binary8> rlnc_decoder;

    rlnc_encoder::factory m_encoder_factory;
    rlnc_decoder::factory m_decoder_factory;
};


kodo_codec* kodo_new_codec()
{
    std::cout << "New kodo codec" << std::endl;
    return new kodo_codec(16, 1400);
}


void kodo_delete_codec(kodo_codec* codec)
{
    delete codec;
}


