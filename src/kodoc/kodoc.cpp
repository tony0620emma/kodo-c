// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "kodoc.h"

#include <cstring>
#include <cstdint>
#include <cassert>
#include <string>

#include <kodo/api/api.hpp>
#include <kodo_fulcrum/api/expansion.hpp>
#include <kodo_fulcrum/api/max_expansion.hpp>
#include <kodo_fulcrum/api/set_expansion.hpp>
#include <kodo_fulcrum/api/inner_symbols.hpp>
#include <kodo_fulcrum/api/max_inner_symbols.hpp>
#include <kodo_fulcrum/api/nested_symbols.hpp>
#include <kodo_fulcrum/api/nested_symbol_size.hpp
#include <kodo_rlnc/api/pre_charging.hpp>
#include <kodo_rlnc/api/pseudo_systematic.hpp>
#include <kodo_rlnc/api/set_pre_charging.hpp>
#include <kodo_rlnc/api/set_pseudo_systematic.hpp>
#include <kodo_rlnc/api/set_width.hpp>
#include <kodo_rlnc/api/set_width_ratio.hpp>
#include <kodo_rlnc/api/width.hpp>
#include <kodo_rlnc/api/width_ratio.hpp>

struct kodo_factory { };
struct kodo_coder { };

//------------------------------------------------------------------
// CONFIGURATION API
//------------------------------------------------------------------

uint8_t kodo_has_codec(int32_t code_type)
{
    bool available = false;

#if !defined(KODOC_DISABLE_RLNC)

#if !defined(KODOC_DISABLE_FULL_VECTOR)
    if (code_type == kodo_full_vector)
    {
        available = true;
    }
#endif
#if !defined(KODOC_DISABLE_ON_THE_FLY)
    if (code_type == kodo_on_the_fly)
    {
        available = true;
    }
#endif
#if !defined(KODOC_DISABLE_SLIDING_WINDOW)
    if (code_type == kodo_sliding_window)
    {
        available = true;
    }
#endif
#if !defined(KODOC_DISABLE_SPARSE_FULL_VECTOR)
    if (code_type == kodo_sparse_full_vector)
    {
        available = true;
    }
#endif
#if !defined(KODOC_DISABLE_SEED)
    if (code_type == kodo_seed)
    {
        available = true;
    }
#endif
#if !defined(KODOC_DISABLE_SPARSE_SEED)
    if (code_type == kodo_sparse_seed)
    {
        available = true;
    }
#endif
#if !defined(KODOC_DISABLE_PERPETUAL)
    if (code_type == kodo_perpetual)
    {
        available = true;
    }
#endif

#endif // !defined(KODOC_DISABLE_RLNC)

#if !defined(KODOC_DISABLE_FULCRUM)
    if (code_type == kodo_fulcrum)
    {
        available = true;
    }
#endif

#if !defined(KODOC_DISABLE_REED_SOLOMON)
    if (code_type == kodo_reed_solomon)
    {
        available = true;
    }
#endif

    return available;
}


//------------------------------------------------------------------
// FACTORY API
//------------------------------------------------------------------

void kodo_delete_factory(kodo_factory_t factory)
{
    auto api = (kodo::api::final_interface*) factory;
    assert(api);
    api->reset();
}

uint32_t kodo_factory_max_symbols(kodo_factory_t factory)
{
    auto api = (kodo::api::final_interface*) factory;
    assert(api);
    return max_symbols(api);
}

uint32_t kodo_factory_max_symbol_size(kodo_factory_t factory)
{
    auto api = (kodo::api::final_interface*) factory;
    assert(api);
    return max_symbol_size(api);
}

uint32_t kodo_factory_max_block_size(kodo_factory_t factory)
{
    auto api = (kodo::api::final_interface*) factory;
    assert(api);
    return max_block_size(api);
}

uint32_t kodo_factory_max_payload_size(kodo_factory_t factory)
{
    auto api = (kodo::api::final_interface*) factory;
    assert(api);
    return max_payload_size(api);
}

void kodo_factory_set_symbols(kodo_factory_t factory, uint32_t symbols)
{
    auto api = (kodo::api::final_interface*) factory;
    assert(api);
    set_symbols(api, symbols);
}

void kodo_factory_set_symbol_size(kodo_factory_t factory, uint32_t symbol_size)
{
    auto api = (kodo::api::final_interface*) factory;
    assert(api);
    set_symbol_size(api, symbol_size);
}

kodo_coder_t kodo_factory_new_coder(kodo_factory_t factory)
{
    auto api = (kodo::api::final_interface*) factory;
    assert(api);
    return (kodo_coder_t) build(api)->keep_alive();
}

void kodo_delete_coder(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    api->reset();
}

//------------------------------------------------------------------
// PAYLOAD API
//------------------------------------------------------------------

uint32_t kodo_payload_size(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    return payload_size(api);
}

void kodo_read_payload(kodo_coder_t decoder, uint8_t* payload)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    read_payload(api, payload);
}

uint32_t kodo_write_payload(kodo_coder_t coder, uint8_t* payload)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    return write_payload(api, payload);
}

uint8_t kodo_has_write_payload(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    return kodo::api::has_interface<kodo::api::write_payload_interface>(api);
}

//------------------------------------------------------------------
// SYMBOL STORAGE API
//------------------------------------------------------------------

uint32_t kodo_block_size(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    return block_size(api);
}

void kodo_set_const_symbols(kodo_coder_t coder, uint8_t* data, uint32_t size)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    set_const_symbols(api, sak::storage(data, size));
}

void kodo_set_const_symbol(kodo_coder_t coder, uint32_t index, uint8_t* data,
                           uint32_t size)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    set_const_symbol(api, index, sak::storage(data, size));
}

void kodo_set_mutable_symbols(kodo_coder_t coder, uint8_t* data, uint32_t size)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    set_mutable_symbols(api, sak::storage(data, size));
}

void kodo_set_mutable_symbol(kodo_coder_t coder, uint32_t index, uint8_t* data,
                             uint32_t size)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    set_mutable_symbol(api, index, sak::storage(data, size));
}

uint32_t kodo_symbol_size(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    return symbol_size(api);
}

uint32_t kodo_symbols(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    return symbols(api);
}

//------------------------------------------------------------------
// CODEC API
//------------------------------------------------------------------

uint8_t kodo_is_complete(kodo_coder_t decoder)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    return is_complete(api);
}

uint8_t kodo_is_partially_complete(kodo_coder_t decoder)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    return is_partially_complete(api);
}

uint8_t kodo_has_feedback_size(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    return kodo::api::has_interface<kodo::api::feedback_size_interface>(api);
}

uint8_t kodo_feedback_size(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    return feedback_size(api);
}

void kodo_read_feedback(kodo_coder_t encoder, uint8_t* feedback)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    read_feedback(api, feedback);
}

uint32_t kodo_write_feedback(kodo_coder_t decoder, uint8_t* feedback)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    return write_feedback(api, feedback);
}

uint32_t kodo_rank(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    return rank(api);
}

uint8_t kodo_is_symbol_pivot(kodo_coder_t decoder, uint32_t index)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    return is_symbol_pivot(api, index);
}

uint8_t kodo_is_symbol_missing(kodo_coder_t decoder, uint32_t index)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    return is_symbol_missing(api, index);
}

uint8_t kodo_is_symbol_partially_decoded(kodo_coder_t decoder, uint32_t index)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    return is_symbol_partially_decoded(api, index);
}

uint8_t kodo_is_symbol_uncoded(kodo_coder_t decoder, uint32_t index)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    return is_symbol_uncoded(api, index);
}

uint32_t kodo_symbols_missing(kodo_coder_t decoder)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    return symbols_missing(api);
}

uint32_t kodo_symbols_partially_decoded(kodo_coder_t decoder)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    return symbols_partially_decoded(api);
}

uint32_t kodo_symbols_uncoded(kodo_coder_t decoder)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    return symbols_uncoded(api);
}

void kodo_read_symbol(kodo_coder_t decoder, uint8_t* symbol_data,
                      uint8_t* coefficients)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    return read_symbol(api, symbol_data, coefficients);
}

void kodo_read_uncoded_symbol(kodo_coder_t decoder, uint8_t* symbol_data,
                              uint32_t index)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    return read_uncoded_symbol(api, symbol_data, index);
}

uint32_t kodo_write_symbol(kodo_coder_t encoder, uint8_t* symbol_data,
                           uint8_t* coefficients)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    return write_symbol(api, symbol_data, coefficients);
}

uint32_t kodo_write_uncoded_symbol(kodo_coder_t encoder, uint8_t* symbol_data,
                                   uint32_t index)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    return write_uncoded_symbol(api, symbol_data, index);
}

//------------------------------------------------------------------
// GENERIC API
//------------------------------------------------------------------

uint8_t kodo_has_partial_decoding_interface(kodo_coder_t decoder)
{
    auto api = (kodo::api::final_interface*) decoder;
    assert(api);
    return kodo::api::has_interface<kodo::api::partial_decoding_interface>(api);
}

uint8_t kodo_has_systematic_interface(kodo_coder_t encoder)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    return kodo::api::has_interface<kodo::api::systematic_interface>(api);
}

uint8_t kodo_is_systematic_on(kodo_coder_t encoder)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    return is_systematic_on(api);
}

void kodo_set_systematic_on(kodo_coder_t encoder)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    set_systematic_on(api);
}

void kodo_set_systematic_off(kodo_coder_t encoder)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    set_systematic_off(api);
}

//------------------------------------------------------------------
// TRACE API
//------------------------------------------------------------------

uint8_t kodo_has_trace_interface(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    return kodo::api::has_interface<kodo::api::trace_interface>(api);
}

void kodo_set_trace_callback(
    kodo_coder_t coder, kodo_trace_callback_t c_callback, void* context)
{
    assert(c_callback);
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    auto callback = [c_callback, context](const std::string& zone,
                                          const std::string& data)
    {
        c_callback(zone.c_str(), data.c_str(), context);
    };
    set_trace_callback(api, callback);
}

void kodo_set_trace_stdout(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    set_trace_stdout(api);
}

void kodo_set_trace_off(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    set_trace_off(api);
}

void kodo_set_zone_prefix(kodo_coder_t coder, const char* prefix)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    set_zone_prefix(api, std::string(prefix));
}

//------------------------------------------------------------------
// SPARSE ENCODER API
//------------------------------------------------------------------

double kodo_density(kodo_coder_t encoder)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    return density(api);
}

void kodo_set_density(kodo_coder_t encoder, double density)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    set_density(api, density);
}

//------------------------------------------------------------------
// PERPETUAL ENCODER API
//------------------------------------------------------------------

uint8_t kodo_pseudo_systematic(kodo_coder_t encoder)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    return kodo::rlnc::api::pseudo_systematic(api);
}

void kodo_set_pseudo_systematic(kodo_coder_t encoder, uint8_t pseudo_systematic)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    kodo::rlnc::api::set_pseudo_systematic(api, pseudo_systematic != 0);
}

uint8_t kodo_pre_charging(kodo_coder_t encoder)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    return kodo::rlnc::api::pre_charging(api);
}

void kodo_set_pre_charging(kodo_coder_t encoder, uint8_t pre_charging)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    kodo::rlnc::api::set_pre_charging(api, pre_charging != 0);
}

uint32_t kodo_width(kodo_coder_t encoder)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    return kodo::rlnc::api::width(api);
}

void kodo_set_width(kodo_coder_t encoder, uint32_t width)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    kodo::rlnc::api::set_width(api, width);
}

double kodo_width_ratio(kodo_coder_t encoder)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    return kodo::rlnc::api::width_ratio(api);
}

void kodo_set_width_ratio(kodo_coder_t encoder, double width_ratio)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    kodo::rlnc::api::set_width_ratio(api, width_ratio);
}

//------------------------------------------------------------------
// FULCRUM CODER API
//------------------------------------------------------------------

uint32_t kodo_expansion(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    return kodo::fulcrum::api::expansion(api);
}

uint32_t kodo_inner_symbols(kodo_coder_t coder)
{
    auto api = (kodo::api::final_interface*) coder;
    assert(api);
    return kodo::fulcrum::api::inner_symbols(api);
}

//------------------------------------------------------------------
// FULCRUM ENCODER API
//------------------------------------------------------------------
uint32_t kodo_nested_symbols(kodo_coder_t encoder)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    return kodo::fulcrum::api::nested_symbols(api);
}

uint32_t kodo_nested_symbol_size(kodo_coder_t encoder)
{
    auto api = (kodo::api::final_interface*) encoder;
    assert(api);
    return kodo::fulcrum::api::nested_symbol_size(api);
}

//------------------------------------------------------------------
// FULCRUM FACTORY API
//------------------------------------------------------------------

uint32_t kodo_factory_max_expansion(kodo_factory_t factory)
{
    auto api = (kodo::api::final_interface*) factory;
    assert(api);
    return kodo::fulcrum::api::max_expansion(api);
}

void kodo_factory_set_expansion(kodo_factory_t factory, uint32_t expansion)
{
    auto api = (kodo::api::final_interface*) factory;
    assert(api);
    kodo::fulcrum::api::set_expansion(api, expansion);
}

uint32_t kodo_factory_max_inner_symbols(kodo_factory_t factory)
{
    auto api = (kodo::api::final_interface*) factory;
    assert(api);
    return kodo::fulcrum::api::max_inner_symbols(api);
}

