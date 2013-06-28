#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//------------------------------------------------------------------
// FACTORY API
//------------------------------------------------------------------

/// Opaque class structures for the two factory types
typedef struct _kodo_factory_t kodo_factory_t;

/// Opaque class structures for the encoders and decoders
typedef struct _kodo_coder_t kodo_coder_t;

/// Builds a new encoder factory
/// @param code_type This parameter determines the encoding algorithms used.
/// @param field_type This parameter determines the finite field type
///        that should be used for the encoding.
/// @param max_symbols The maximum number of symbols supported by encoders
///        built with this factory.
/// @param max_symbol_size The maximum symbol size in bytes supported by
///        encoders built using the returned factory
/// @return A new factory capable of building encoders using for the
///         selected parameters.
kodo_factory_t*
kodo_new_encoder_factory(size_t code_type, size_t field_type,
                         uint32_t max_symbols, uint32_t max_symbol_size);

/// Builds a new decoder factory
/// @param code_type This parameter determines the decoding algorithms used.
/// @param field_type This parameter determines the finite field type
///        that should be used for the decoding.
/// @param max_symbols The maximum number of symbols supported by decoders
///        built with this factory.
/// @param max_symbol_size The maximum symbol size in bytes supported by
///        decoders built using the returned factory
/// @return A new factory capable of building decoders using for the
///         selected parameters.
kodo_factory_t*
kodo_new_decoder_factory(size_t code_type, size_t field_type,
                         uint32_t max_symbols, uint32_t max_symbol_size);

/// Deallocates and releases the memory consumed by the encoder factory
/// @param factory Pointer to the encoder factory which should be deallocated
void kodo_delete_encoder_factory(kodo_factory_t* factory);

/// Deallocates and releases the memory consumed by the encoder factory
/// @param factory Pointer to the encoder factory which should be deallocated
void kodo_delete_decoder_factory(kodo_factory_t* factory);

/// @param factory Pointer to the factory to query
/// @return the maximum number of symbols supported by the factory
uint32_t kodo_max_symbols(kodo_factory_t* factory);

/// @param factory Pointer to the factory to query
/// @return the maximum symbol size in bytes supported by the factory
uint32_t kodo_max_symbol_size(kodo_factory_t* factory);

/// @param factory Pointer to the factory to query
/// @return The maximum amount of data encoded / decoded in bytes.
///         This is calculated by multiplying the maximum number
///         of symbols encoded / decoded by the maximum size of
///         a symbol.
uint32_t kodo_max_block_size(kodo_factory_t* factory);

/// @param factory Pointer to the factory to query
/// @return the maximum required payload buffer size in bytes
uint32_t kodo_max_payload_size(kodo_factory_t* factory);

/// Sets the number of symbols which should be used for the subsequent
/// encoders / decoders built with the specified factory. The value must
/// be below the max symbols used for the specific factory.
/// @param factory Pointer to the factory which should be configured
void kodo_set_symbols(kodo_factory_t* factory, uint32_t symbols);

/// Sets the number of symbols which should be used for the subsequent
/// encoders / decoders built with the specified factory. The value must
/// be below the max symbols used for the specific factory.
/// @param factory Pointer to the factory which should be configured
void kodo_set_symbol_size(kodo_factory_t* factory, uint32_t symbol_size);

/// Builds a new encoder using the specified factory
/// @param factory Pointer to the encoder factory which should be used to
///        build the encoder
kodo_coder_t* kodo_new_encoder(kodo_factory_t* factory);

/// Builds a new encoder using the specified factory
/// @param factory Pointer to the encoder factory which should be used to
///        build the encoder
kodo_coder_t* kodo_new_decoder(kodo_factory_t* factory);

/// Deallocates and releases the memory consumed by the encoder factory
/// @param factory Pointer to the encoder factory which should be deallocated
void kodo_delete_encoder(kodo_coder_t* encoder);

/// Deallocates and releases the memory consumed by the encoder factory
/// @param factory Pointer to the encoder factory which should be deallocated
void kodo_delete_decoder(kodo_coder_t* decoder);








uint32_t kodo_block_size(void* coder);
uint32_t kodo_payload_size(void* coder);

uint32_t kodo_encode(void* encoder, uint8_t* data);
void kodo_set_symbols(void* encoder, const uint8_t* data, uint32_t size);
void kodo_set_symbol(void* encoder, uint32_t index, const uint8_t* data, uint32_t size);


void kodo_decode(void* decoder, uint8_t *data);
uint8_t kodo_is_complete(void* decoder);
uint32_t kodo_rank(void* decoder);
void kodo_copy_symbols(void* decoder, uint8_t* data, uint32_t size);


/// Constants for selecting the finite field
extern const size_t kodo_binary;
extern const size_t kodo_binary8;
extern const size_t kodo_binary16;


/// Constants for select in the encoder/decoder
extern const size_t kodo_full_rlnc;
// extern const size_t kodo_seed_rlnc;
// extern const size_t kodo_reed_solomon;



#ifdef __cplusplus
}
#endif




