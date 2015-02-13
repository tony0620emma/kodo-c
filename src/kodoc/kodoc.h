// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <stdint.h>

#if defined(_MSC_VER)
    #if defined(KODOC_STATIC)
        // When building a static library, the API define should be blank
        #define KODOC_API
    #elif defined(KODOC_DLL_EXPORTS)
        // When building the DLL, the API symbols must be exported
        #define KODOC_API __declspec(dllexport)
    #else
        // When a program uses the DLL, the API symbols must be imported
        #define KODOC_API __declspec(dllimport)
    #endif
#else
  #if __GNUC__ >= 4
    // When building a shared library, only the API symbols with the 'default'
    // visibility should be exported to hide all other symbols. All source
    // files should be compiled with the '-fvisibility=hidden' and
    // '-fvisibility-inlines-hidden' flags to achieve this.
    #define KODOC_API __attribute__ ((visibility ("default")))
  #else
    #define KODOC_API
  #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/// Callback function type used for tracing
typedef void (*kodo_trace_callback_t)(const char*, const char*);

//------------------------------------------------------------------
// FACTORY API
//------------------------------------------------------------------

/// Opaque pointer used for the encoder and decoder factories
typedef struct kodo_factory* kodo_factory_t;

/// Opaque pointer used for encoders and decoders
typedef struct kodo_coder* kodo_coder_t;

/// Enum specifying the available finite fields
/// Note: the size of the enum type cannot be guaranteed, so the int32_t type
/// is used in the API calls to pass the enum values
typedef enum
{
    kodo_binary,
    kodo_binary4,
    kodo_binary8,
    kodo_binary16,
    kodo_prime2325
}
kodo_finite_field;

/// Enum specifying the available code types
/// Note: the size of the enum type cannot be guaranteed, so the int32_t type
/// is used in the API calls to pass the enum values
typedef enum
{
    kodo_full_rlnc,
    kodo_on_the_fly,
    kodo_sliding_window
}
kodo_code_type;

/// Enum specifying the available trace modes
/// Note: the size of the enum type cannot be guaranteed, so the int32_t type
/// is used in the API calls to pass the enum values
typedef enum
{
    kodo_trace_disabled,
    kodo_trace_enabled
}
kodo_trace_mode;

/// Builds a new encoder factory (for deep storage encoders)
/// @param code_type This parameter determines the encoding algorithms used.
/// @param finite_field This parameter determines the finite field type
///        that should be used for the encoding.
/// @param max_symbols The maximum number of symbols supported by encoders
///        built with this factory.
/// @param max_symbol_size The maximum symbol size in bytes supported by
///        encoders built using the returned factory
/// @param trace_mode Determines which trace mode should be used.
/// @return A new factory capable of building encoders using the
///         selected parameters.
KODOC_API
kodo_factory_t kodo_new_encoder_factory(
    int32_t code_type, int32_t finite_field,
    uint32_t max_symbols, uint32_t max_symbol_size,
    int32_t trace_mode);

/// Builds a new decoder factory (for deep storage decoders)
/// @param code_type This parameter determines the decoding algorithms used.
/// @param finite_field This parameter determines the finite field type
///        that should be used for the decoding.
/// @param max_symbols The maximum number of symbols supported by decoders
///        built with this factory.
/// @param max_symbol_size The maximum symbol size in bytes supported by
///        decoders built using the returned factory
/// @param trace_mode Determines which trace mode should be used.
/// @return A new factory capable of building decoders using the
///         selected parameters.
KODOC_API
kodo_factory_t kodo_new_decoder_factory(
    int32_t code_type, int32_t finite_field,
    uint32_t max_symbols, uint32_t max_symbol_size,
    int32_t trace_mode);

/// Builds a new encoder factory (for shallow storage encoders)
/// @param code_type This parameter determines the encoding algorithms used.
/// @param finite_field This parameter determines the finite field type
///        that should be used for the encoding.
/// @param max_symbols The maximum number of symbols supported by encoders
///        built with this factory.
/// @param max_symbol_size The maximum symbol size in bytes supported by
///        encoders built using the returned factory
/// @param trace_mode Determines which trace mode should be used.
/// @return A new factory capable of building encoders using the
///         selected parameters.
KODOC_API
kodo_factory_t kodo_new_shallow_encoder_factory(
    int32_t code_type, int32_t finite_field,
    uint32_t max_symbols, uint32_t max_symbol_size,
    int32_t trace_mode);

/// Builds a new decoder factory (for shallow storage decoders)
/// @param code_type This parameter determines the decoding algorithms used.
/// @param finite_field This parameter determines the finite field type
///        that should be used for the decoding.
/// @param max_symbols The maximum number of symbols supported by decoders
///        built with this factory.
/// @param max_symbol_size The maximum symbol size in bytes supported by
///        decoders built using the returned factory
/// @param trace_mode Determines which trace mode should be used.
/// @return A new factory capable of building decoders using the
///         selected parameters.
KODOC_API
kodo_factory_t kodo_new_shallow_decoder_factory(
    int32_t code_type, int32_t finite_field,
    uint32_t max_symbols, uint32_t max_symbol_size,
    int32_t trace_mode);

/// Deallocates and releases the memory consumed by the encoder factory
/// @param factory The encoder factory which should be deallocated
KODOC_API
void kodo_delete_encoder_factory(kodo_factory_t factory);

/// Deallocates and releases the memory consumed by the decoder factory
/// @param factory The decoder factory which should be deallocated
KODOC_API
void kodo_delete_decoder_factory(kodo_factory_t factory);

/// @param factory The factory to query
/// @return the maximum number of symbols supported by the factory
KODOC_API
uint32_t kodo_factory_max_symbols(kodo_factory_t factory);

/// @param factory The factory to query
/// @return the maximum symbol size in bytes supported by the factory
KODOC_API
uint32_t kodo_factory_max_symbol_size(kodo_factory_t factory);

/// @param factory The factory to query
/// @return The maximum amount of data encoded / decoded in bytes.
///         This is calculated by multiplying the maximum number of symbols
///         encoded / decoded by the maximum size of a symbol.
KODOC_API
uint32_t kodo_factory_max_block_size(kodo_factory_t factory);

/// @param factory The factory to query
/// @return the maximum required payload buffer size in bytes
KODOC_API
uint32_t kodo_factory_max_payload_size(kodo_factory_t factory);

/// Sets the number of symbols which should be used for the subsequent
/// encoders / decoders built with the specified factory. The value must
/// be below the max symbols used for the specific factory.
/// @param factory The factory which should be configured
/// @param symbols The number of symbols used for the next encoder/decoder
///        built with the factory.
KODOC_API
void kodo_factory_set_symbols(kodo_factory_t factory, uint32_t symbols);

/// Sets the number of symbols which should be used for the subsequent
/// encoders / decoders built with the specified factory. The value must
/// be below the max symbols used for the specific factory.
/// @param factory The factory which should be configured
/// @param symbols_size The symbol size used for the next encoder/decoder
///        built with the factory.
KODOC_API
void kodo_factory_set_symbol_size(kodo_factory_t factory,
                                  uint32_t symbol_size);

/// Builds a new encoder using the specified factory
/// @param factory The encoder factory which should be used to
///        build the encoder
/// @return The new encoder
KODOC_API
kodo_coder_t kodo_factory_new_encoder(kodo_factory_t factory);

/// Builds a new decoder using the specified factory
/// @param factory The decoder factory which should be used to
///        build the decoder
/// @return The new decoder
KODOC_API
kodo_coder_t kodo_factory_new_decoder(kodo_factory_t factory);

/// Deallocates and releases the memory consumed by an encoder
/// @param encoder The encoder which should be deallocated
KODOC_API
void kodo_delete_encoder(kodo_coder_t encoder);

/// Deallocates and releases the memory consumed by a decoder
/// @param decoder The decoder which should be deallocated
KODOC_API
void kodo_delete_decoder(kodo_coder_t decoder);

//------------------------------------------------------------------
// PAYLOAD API
//------------------------------------------------------------------

/// @param coder The encoder or decoder to query.
/// @return The required payload buffer size in bytes
KODOC_API
uint32_t kodo_payload_size(kodo_coder_t coder);

/// Decodes an encoded symbol stored in the payload buffer.
/// @param decoder The decoder to use.
/// @param payload The buffer storing the payload of an encoded symbol.
///        The payload buffer may be changed by the decode function,
///        an cannot be reused. If the payload is needed in several places
///        make sure to keep a copy of the original payload.
KODOC_API
void kodo_read_payload(kodo_coder_t decoder, uint8_t* payload);

/// (Re/En)codes a symbol into the provided buffer.
/// @param coder The (de/en)coder to use.
/// @param payload The buffer which should contain the (re/en)coded
///        symbol.
/// @return The total bytes used from the payload buffer
KODOC_API
uint32_t kodo_write_payload(kodo_coder_t coder, uint8_t* payload);

//------------------------------------------------------------------
// SYMBOL STORAGE API
//------------------------------------------------------------------

/// @param coder The coder to query.
/// @return the block size, i.e. the total size in bytes
///         that this coder operates on.
KODOC_API
uint32_t kodo_block_size(kodo_coder_t coder);

/// Sets the storage for the source symbols. This will specify all
/// symbols also in the case of partial data. If this is not desired,
/// then the symbols should be specified individually. This also
/// means that it is the responsibility of the user to communicate
/// how many of the bytes transmitted are application data.
/// @param encoder The encoder which will encode the data
/// @param data The buffer containing the data to be encoded
/// @param size The size of the buffer to be encoded
KODOC_API
void kodo_set_symbols(kodo_coder_t encoder, uint8_t* data, uint32_t size);

/// Sets a data of a symbol.
/// @param encoder The encoder which will encode the data
/// @param index the index of the symbol into the coding block
/// @param data The buffer containing the data to be encoded
/// @param size The size of the buffer to be encoded
KODOC_API
void kodo_set_symbol(kodo_coder_t encoder, uint32_t index,
                     uint8_t* data, uint32_t size);

/// Copies the decoded symbols to the dest buffer.
/// @param decoder The decoder which contains the data to be
///        copied.
/// @param data The destination buffer to which the data should be copied
/// @param size The size of the data to be copied
KODOC_API
void kodo_copy_symbols(kodo_coder_t decoder, uint8_t* data, uint32_t size);

/// Copies a specific symbol to the data buffer.
/// @param decoder The decoder which contains the data to be
///        copied.
/// @param index The index of the symbol to copy
/// @param data The destination buffer to which the data should be copied
/// @param size The size of the data to be copied
KODOC_API
void kodo_copy_symbol(kodo_coder_t decoder, uint32_t index,
                      uint8_t* data, uint32_t size);

/// @param coder The encoder/decoder to check
/// @return The size of a symbol in bytes
KODOC_API
uint32_t kodo_symbol_size(kodo_coder_t coder);

/// @param coder The encoder/decoder to check
/// @return The number of symbols in a encoder/decoder
KODOC_API
uint32_t kodo_symbols(kodo_coder_t coder);

//------------------------------------------------------------------
// CODEC API
//------------------------------------------------------------------

/// Checks whether decoding is complete.
/// @param decoder The decoder to query
/// @return Non-zero value if the decoding is complete, otherwise 0
KODOC_API
uint8_t kodo_is_complete(kodo_coder_t decoder);

/// Check whether decoding is partially complete. This means that some
/// symbols in the decoder has been fully decoded. You can use the
/// kodo_symbol_pivot(uint32_t) to determine which symbols.
/// @param decoder The decoder to query
/// @return Non-zero value if the decoding is partially complete, otherwise 0
KODOC_API
uint8_t kodo_is_partial_complete(kodo_coder_t decoder);

/// The rank of a decoder indicates how many symbols have been decoded
/// or partially decoded. The rank of an encoder indicates how many symbols
/// are available for encoding.
/// @param coder The coder to query
/// @return The rank of the decoder or encoder
KODOC_API
uint32_t kodo_rank(kodo_coder_t coder);

/// Checks whether the encoder or decoder can use/provide feedback information.
/// The encoder can disregard some symbols if the feedback from decoder
/// indicates that those symbols were already decoded.
/// @param coder The encoder/decoder to query
/// @return Non-zero value if feedback is supported, otherwise 0
KODOC_API
uint8_t kodo_has_feedback_size(kodo_coder_t coder);

/// @param coder The encoder/decoder to check
/// @return The size of the required feedback buffer in bytes
KODOC_API
uint8_t kodo_feedback_size(kodo_coder_t coder);

/// Reads the feedback information from the provided buffer.
/// @param encoder The encoder to use.
/// @param feedback The buffer which contains the feedback information
KODOC_API
void kodo_read_feedback(kodo_coder_t encoder, uint8_t* feedback);

/// Writes the feedback information into the provided buffer.
/// @param decoder The decoder to use.
/// @param feedback The buffer which should contain the feedback information.
KODOC_API
void kodo_write_feedback(kodo_coder_t decoder, uint8_t* feedback);

/// Indicates whether a symbol is defined in the coding matrix
/// of encoder or decoder. A symbol with a pivot element might not be fully
/// decoded in the coding matrix of a decoder, therefore use the
/// kodo_is_symbol_uncoded() function to check if a symbol is fully decoded.
/// @param coder The encoder/decoder to query
/// @param index Index of the symbol whose state should be checked
/// @return Non-zero value if the symbol is defined, otherwise 0
KODOC_API
uint8_t kodo_symbol_pivot(kodo_coder_t coder, uint32_t index);

/// Indicates whether a symbol is available in an uncoded (i.e. fully decoded)
/// form in an encoder or decoder.
/// @param coder The decoder to query
/// @param index Index of the symbol whose state should be checked
/// @return Non-zero value if the symbol is , otherwise 0
KODOC_API
uint8_t kodo_is_symbol_uncoded(kodo_coder_t decoder, uint32_t index);

/// @param coder The decoder to query
/// @return The number of uncoded symbols in the decoder
KODOC_API
uint32_t kodo_symbols_uncoded(kodo_coder_t decoder);

/// @param coder The decoder to query
/// @return The number of symbols seen by the decoder. The seen symbols might
///         not be fully decoded.
KODOC_API
uint32_t kodo_symbols_seen(kodo_coder_t decoder);

/// Reads and decodes an encoded symbol according to the coding
/// coefficients stored in the corresponding symbol_id.
///
/// @param decoder The decoder to use.
/// @param symbol_data The encoded symbol
/// @param coefficients The coding coefficients used to
///        create the encoded symbol
KODOC_API
void kodo_read_symbol(kodo_coder_t decoder, uint8_t* symbol_data,
                      uint8_t* coefficients);

/// Reads and decodes a systematic/uncoded symbol with the corresponding
/// symbol index.
///
/// @param decoder The decoder to use.
/// @param symbol_data The uncoded source symbol.
/// @param index The index of this uncoded symbol in the data block.
KODOC_API
void kodo_read_uncoded_symbol(kodo_coder_t decoder, uint8_t* symbol_data,
                              uint32_t index);

/// Writes an encoded symbol according to the provided symbol coefficients.
///
/// @param encoder The encoder to use.
/// @param symbol_data The destination buffer for the encoded symbol
/// @param coefficients At this point the symbol id should be
///        initialized with the desired coding coefficients.
/// @return The number of bytes used.
KODOC_API
uint32_t kodo_write_symbol(kodo_coder_t encoder, uint8_t* symbol_data,
                           uint8_t* coefficients);

/// Writes a systematic/uncoded symbol that corresponds to the provided
/// symbol index.
///
/// @param encoder The encoder to use.
/// @param symbol_data The destination of the uncoded source symbol.
/// @param index The index of this uncoded symbol in the data block.
/// @return The number of bytes used.
KODOC_API
uint32_t kodo_write_uncoded_symbol(kodo_coder_t encoder, uint8_t* symbol_data,
                                   uint32_t index);

//------------------------------------------------------------------
// GENERIC API
//------------------------------------------------------------------

/// Check whether the decoder has support for partial decoding tracker. This
/// basically means that the decoder will be able to decode symbols on the fly.
/// If the decoder supports the partial decoding tracker, then the function
/// kodo_is_partial_complete() may be used to determine whether some of the
/// symbols has been fully decoded and therefore can be copied out of the
/// decoder.
/// @param coder The decoder to query
/// @return Non-zero value if the decoder is partially decoded, otherwise 0
KODOC_API
uint8_t kodo_has_partial_decoding_tracker(kodo_coder_t decoder);

/// Returns whether an encoder has systematic capabilities
/// @param encoder The encoder
/// @return Non-zero if the encoder supports the systematic mode, otherwise 0
KODOC_API
uint8_t kodo_has_set_systematic_off(kodo_coder_t encoder);

/// Returns whether the encoder is in the systematic mode, i.e. if it will
/// initially send the original source symbols with a simple header.
///
/// @param encoder The encoder
/// @return Non-zero if the encoder is in the systematic mode, otherwise 0
KODOC_API
uint8_t kodo_is_systematic_on(kodo_coder_t encoder);

/// Switches the systematic encoding on
/// @param encoder The encoder
KODOC_API
void kodo_set_systematic_on(kodo_coder_t encoder);

/// Switches the systematic encoding off
/// @param encoder The encoder
KODOC_API
void kodo_set_systematic_off(kodo_coder_t encoder);

//------------------------------------------------------------------
// TRACE API
//------------------------------------------------------------------

/// Returns whether an encoder or decoder has trace capabilities
/// @param coder The encoder/decoder to query
/// @return Non-zero value if tracing is supported, otherwise 0
KODOC_API
uint8_t kodo_has_trace(kodo_coder_t coder);

/// Prints the trace output of an encoder or decoder to the standard output
/// @param coder The encoder/decoder to use
KODOC_API
void kodo_trace(kodo_coder_t coder);

/// Forwards the trace output of an encoder or decoder to a custom callback
/// @param coder The encoder/decoder to use
/// @param callback The callback that processes the trace output
KODOC_API
void kodo_trace_callback(kodo_coder_t coder, kodo_trace_callback_t callback);

#ifdef __cplusplus
}
#endif
