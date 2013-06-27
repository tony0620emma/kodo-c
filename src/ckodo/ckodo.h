#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/// Handle for a kodo factory
typedef struct kodo_decoder_factory_ kodo_decoder_factory;
typedef struct kodo_encoder_factory_ kodo_encoder_factory;

/// Handle for a kodo encoder
typedef struct kodo_encoder_ kodo_encoder;

/// Handle for a kodo decoder
typedef struct kodo_decoder_ kodo_decoder;

//------------------------------------------------------------------
// FACTORY API
//------------------------------------------------------------------

kodo_encoder_factory*
kodo_new_encoder_factory(size_t code_type, size_t field_type,
                         uint32_t max_symbols, uint32_t max_symbol_size);

kodo_decoder_factory*
kodo_new_decoder_factory(size_t code_type, size_t field_type,
                         uint32_t max_symbols, uint32_t max_symbol_size);

kodo_encoder* kodo_new_encoder(kodo_encoder_factory* factory);
kodo_decoder* kodo_new_decoder(kodo_decoder_factory* factory);

void kodo_delete_encoder_factory(kodo_encoder_factory* factory);
void kodo_delete_decoder_factory(kodo_decoder_factory* factory);
void kodo_delete_encoder(kodo_encoder* encoder);
void kodo_delete_decoder(kodo_decoder* decoder);


/// @return the maximum number of symbols in a block
uint32_t kodo_max_symbols(void* factory);

/// @return the maximum symbol size in bytes
uint32_t kodo_max_symbol_size(void* factory);

/// @return The maximum amount of data encoded / decoded in bytes.
///         This is calculated by multiplying the maximum number
///         of symbols encoded / decoded by the maximum size of
///         a symbol.
uint32_t kodo_max_block_size();

/// @return the maximum required payload buffer size in bytes
uint32_t kodo_max_payload_size();




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




