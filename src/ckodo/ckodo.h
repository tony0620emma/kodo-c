// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __INTEL_COMPILER
    #pragma byte_order (push, littleendian)
    #pragma extern_prefix (push, "")
#endif

typedef uint8_t (*kodo_filter_function_t)(const char*);

//------------------------------------------------------------------
// FACTORY API
//------------------------------------------------------------------

/// Opaque class structures for the two factory types
typedef struct _kodo_factory_t kodo_factory_t;

/// Opaque class structures for the encoders and decoders
typedef struct _kodo_coder_t kodo_coder_t;

/// Constants for selecting the finite field
extern const size_t kodo_binary;
extern const size_t kodo_binary8;
extern const size_t kodo_binary16;

/// Constants for select in the encoder/decoder
extern const size_t kodo_full_rlnc;
    //extern const size_t kodo_debug_full_rlnc;
extern const size_t kodo_on_the_fly;
    //extern const size_t kodo_debug_on_the_fly;
extern const size_t kodo_sliding_window;

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
                         uint32_t max_symbols, uint32_t max_symbol_size,
                         uint32_t trace_enabled);

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
                         uint32_t max_symbols, uint32_t max_symbol_size,
                         uint32_t trace_enabled);

/// Deallocates and releases the memory consumed by the encoder factory
/// @param factory Pointer to the encoder factory which should be deallocated
void kodo_delete_encoder_factory(kodo_factory_t* factory);

/// Deallocates and releases the memory consumed by the decoder factory
/// @param factory Pointer to the decoder factory which should be deallocated
void kodo_delete_decoder_factory(kodo_factory_t* factory);

/// @param factory Pointer to the factory to query
/// @return the maximum number of symbols supported by the factory
uint32_t kodo_factory_max_symbols(kodo_factory_t* factory);

/// @param factory Pointer to the factory to query
/// @return the maximum symbol size in bytes supported by the factory
uint32_t kodo_factory_max_symbol_size(kodo_factory_t* factory);

/// @param factory Pointer to the factory to query
/// @return The maximum amount of data encoded / decoded in bytes.
///         This is calculated by multiplying the maximum number
///         of symbols encoded / decoded by the maximum size of
///         a symbol.
uint32_t kodo_factory_max_block_size(kodo_factory_t* factory);

/// @param factory Pointer to the factory to query
/// @return the maximum required payload buffer size in bytes
uint32_t kodo_factory_max_payload_size(kodo_factory_t* factory);

/// Sets the number of symbols which should be used for the subsequent
/// encoders / decoders built with the specified factory. The value must
/// be below the max symbols used for the specific factory.
/// @param factory Pointer to the factory which should be configured
/// @param symbols The number of symbols used for the next encoder/decoder
///        built with the factory.
void kodo_factory_set_symbols(kodo_factory_t* factory, uint32_t symbols);

/// Sets the number of symbols which should be used for the subsequent
/// encoders / decoders built with the specified factory. The value must
/// be below the max symbols used for the specific factory.
/// @param factory Pointer to the factory which should be configured
/// @param symbols_size The symbol size used for the next encoder/decoder
///        built with the factory.
void kodo_factory_set_symbol_size(kodo_factory_t* factory,
                                  uint32_t symbol_size);

/// Builds a new encoder using the specified factory
/// @param factory Pointer to the encoder factory which should be used to
///        build the encoder
/// @return The new encoder built
kodo_coder_t* kodo_factory_new_encoder(kodo_factory_t* factory);

/// Builds a new encoder using the specified factory
/// @param factory Pointer to the encoder factory which should be used to
///        build the encoder
/// @return The new decoder built
kodo_coder_t* kodo_factory_new_decoder(kodo_factory_t* factory);

/// Deallocates and releases the memory consumed by the encoder factory
/// @param factory Pointer to the encoder factory which should be deallocated
void kodo_delete_encoder(kodo_coder_t* encoder);

/// Deallocates and releases the memory consumed by the encoder factory
/// @param factory Pointer to the encoder factory which should be deallocated
void kodo_delete_decoder(kodo_coder_t* decoder);

//------------------------------------------------------------------
// PAYLOAD API
//------------------------------------------------------------------

/// @param coder Pointer to the encoder or decoder to query.
/// @return the required payload buffer size in bytes
uint32_t kodo_payload_size(kodo_coder_t* coder);

/// Encodes a symbol into the provided buffer.
/// @param coder Pointer to the encoder to use.
/// @param payload The buffer which should contain the encoded
///        symbol.
/// @return the total bytes used from the payload buffer
uint32_t kodo_encode(kodo_coder_t* encoder, uint8_t* payload);

/// Decodes an encoded symbol stored in the payload buffer.
/// @param coder Pointer to the decoder to use.
/// @param payload The buffer storing the payload of an encoded symbol.
///        The payload buffer may be changed by the decode function,
///        an cannot be reused. If the payload is needed in several places
///        make sure to keep a copy of the original payload.
void kodo_decode(kodo_coder_t* decoder, uint8_t* payload);

/// Recodes a symbol into the provided buffer. This function is special for
/// network codes.
/// @param coder Pointer to the decoder to use.
/// @param payload The buffer which should contain the recoded
///        symbol.
/// @return the total bytes used from the payload buffer
uint32_t kodo_recode(kodo_coder_t* decoder, uint8_t* payload);

//------------------------------------------------------------------
// SYMBOL STORAGE API
//------------------------------------------------------------------

/// @param coder Pointer to the coder to query.
/// @return the block size i.e. the total size in bytes
///         that this coder operates on. Users may
///         use the bytes_used() function provided in the
///         symbol storage layers to see how many of those
///         bytes are then used.
uint32_t kodo_block_size(kodo_coder_t* coder);

/// Sets the storage for the source symbols. This will specify all
/// symbols also in the case of partial data. If this is not desired
/// then the symbols should be specified individually. This also
/// means that it is the responsibility of the user to communicate
/// how many of the bytes transmitted are application data.
/// @param encoder Pointer to the encoder which will encode the data
/// @param data The buffer containing the data to be encoded
/// @param size The size of the buffer to be encoded
void kodo_set_symbols(kodo_coder_t* encoder, const uint8_t* data,
                      uint32_t size);

/// Sets a data of a symbol.
/// @param encoder Pointer to the encoder which will encode the data
/// @param index the index of the symbol into the coding block
/// @param data The buffer containing the data to be encoded
/// @param size The size of the buffer to be encoded
void kodo_set_symbol(kodo_coder_t* encoder, uint32_t index,
                     const uint8_t* data, uint32_t size);

/// Copies the decoded symbols to the dest buffer.
/// @param decoder Pointer to the decoder which contains the data to be
///        copied.
/// @param data The destination buffer to which the data should be copied
/// @param size The size of the data to be copied
void kodo_copy_symbols(kodo_coder_t* decoder, uint8_t* data, uint32_t size);

/// Copies a specific symbol to the data buffer.
/// @param decoder Pointer to the decoder which contains the data to be
///        copied.
/// @param index The index of the symbol to copy
/// @param data The destination buffer to which the data should be copied
/// @param size The size of the data to be copied
void kodo_copy_symbol(kodo_coder_t* decoder, uint32_t index,
                      uint8_t* data, uint32_t size);

/// @param coder Pointer to the encoder/decoder to check
/// @return The size of a symbol in bytes
uint32_t kodo_symbol_size(kodo_coder_t* coder);

/// @param coder Pointer to the encoder/decoder to check
/// @return The number of symbols in a encoder/decoder
uint32_t kodo_symbols(kodo_coder_t* coder);

//------------------------------------------------------------------
// CODEC API
//------------------------------------------------------------------

/// Check whether decoding is complete.
/// @param decoder Pointer to the decoder to query
/// @return true if the decoding is complete
uint8_t kodo_is_complete(kodo_coder_t* decoder);

/// Check whether decoding is partially complete. This means that some
/// symbols in the decoder has been fully decoded. You can use the
/// kodo_symbol_pivot(uint32_t) to determine which symbols.
/// @param decoder Pointer to the decoder to query
/// @return true if the decoding is partially complete
uint8_t kodo_is_partial_complete(kodo_coder_t* decoder);

/// The rank of a decoder states how many symbols have been decoded
/// or partially decoded. The rank of an encoder states how many symbols
/// are available for encoding.
/// @param coder Pointer to the coder to query
/// @return the rank of the decoder or encoder
uint32_t kodo_rank(kodo_coder_t* coder);

uint8_t kodo_feedback_size(kodo_coder_t* encoder);
/// The symbol pivot indicates whether a symbol is available to either an
/// encoder or decoder.
/// @return 1 if the symbol is available otherwise 0.
uint8_t kodo_symbol_pivot(kodo_coder_t* coder, uint32_t index);

/// @param index Index of the symbol whose state should be checked
/// @return 1 if the symbol is decoded otherwise 0
uint8_t kodo_is_symbol_uncoded(kodo_coder_t* coder, uint32_t index);

/// @return the amount of uncoded symbols
uint32_t kodo_symbols_uncoded(kodo_coder_t* decoder);

uint32_t kodo_symbols_seen(kodo_coder_t* decoder);

//------------------------------------------------------------------
// GENERIC API
//------------------------------------------------------------------

/// Check whether the decoder has support for partial decoding tracker. This
/// basically means that the decoder will be able to decode symbols on the fly.
/// If the decoder supports the partial decoding tracker, then the function
/// kodo_is_partial_complete() may be used to determine whether some of the
/// symbols has been fully decoded and therefore can be copied out of the
/// decoder.
/// @param coder Pointer to the decoder to query
/// @return Non-zero value if the decoder is partially decoded otherwise zero
uint8_t kodo_has_partial_decoding_tracker(kodo_coder_t* decoder);

/// Returns whether an encoder has systematic capabilities
/// @param encoder Pointer to the encoder
/// @return Non-zero if the encoder supports the systematic operations
///         otherwise zero
uint8_t kodo_has_systematic_encoder(kodo_coder_t* encoder);

/// Returns whether the encoder is in the systematic mode i.e. it will initially
/// send the original source symbols
///
/// @param encoder Pointer to the encoder
/// @return Non-zero if the encoder is in the systematic state otherwise zero
uint8_t kodo_is_systematic_on(kodo_coder_t* encoder);

/// Switches the systematic encoding on
/// @param encoder Pointer to the encoder
void kodo_set_systematic_on(kodo_coder_t* encoder);

/// Switches the systematic encoding off
/// @param encoder Pointer to the encoder
void kodo_set_systematic_off(kodo_coder_t* encoder);

//------------------------------------------------------------------
// TRACE API
//------------------------------------------------------------------

uint8_t kodo_has_trace(kodo_coder_t* coder);

void kodo_trace_filter(kodo_coder_t* coder, kodo_filter_function_t filter);

void kodo_trace(kodo_coder_t* coder);


#ifdef __INTEL_COMPILER
    #pragma byte_order pop
    #pragma extern_prefix pop
#endif

#ifdef __cplusplus
}
#endif
