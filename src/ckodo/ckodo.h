#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/// Handle for a kodo factory
// typedef struct kodo_decoder_factory_ kodo_decoder_factory;
// typedef struct kodo_encoder_factory_ kodo_encoder_factory;

// /// Handle for a kodo encoder
// typedef struct kodo_encoder_ kodo_encoder;

// /// Handle for a kodo decoder
// typedef struct kodo_decoder_ kodo_decoder;

//------------------------------------------------------------------
// FACTORY API
//------------------------------------------------------------------

void* kodo_new_encoder_factory(size_t code_type, size_t field_type,
                               uint32_t max_symbols, uint32_t max_symbol_size);

void* kodo_new_decoder_factory(size_t code_type, size_t field_type,
                               uint32_t max_symbols, uint32_t max_symbol_size);

void kodo_delete_encoder_factory(void* factory);
void kodo_delete_decoder_factory(void* factory);

void* kodo_new_encoder(void* factory);
void* kodo_new_decoder(void* factory);

void kodo_delete_encoder(void *encoder);
void kodo_delete_decoder(void *decoder);


/// @return the maximum number of symbols in a block
uint32_t kodo_max_symbols(void* factory);

/// @return the maximum symbol size in bytes
uint32_t kodo_max_symbol_size(void* factory);

/// @return The maximum amount of data encoded / decoded in bytes.
///         This is calculated by multiplying the maximum number
///         of symbols encoded / decoded by the maximum size of
///         a symbol.
uint32_t kodo_max_block_size(void* factory);

/// @return the maximum required payload buffer size in bytes
uint32_t kodo_max_payload_size(void* factory);

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




