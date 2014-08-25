// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing
#include <stdint.h>

#include<ckodo/ckodo.h>


int main(){

    uint8_t max_symbols = 16;
    uint8_t max_symbol_size = 160;

    size_t algorithm = sliding_window;
    size_t finite_field = kodo_binary8;

    uint8_t trace_enabled = 1;

    kodo_factory_t* encoder_factory =
        kodo_new_encoder_factory(algorithm, finite_field,
                                 max_symbols, max_symbol_size,
                                 trace_enabled);

    kodo_factory_t* decoder_factory =
        kodo_new_decoder_factory(algorithm, finite_field,
                                 max_symbols, max_symbol_size, 
                                 trace_enabled);

    // If we wanted to build an encoder of decoder with a smaller number of
    // symbols or a different symbol size, then this can be adjusted using the
    // following functions:
    // kodo_factory_set_symbols(...) and kodo_factory_set_symbol_size(...)
    // We can however not exceed the maximum values which was used when building
    // the factory.

    kodo_coder_t* encoder = kodo_factory_new_encoder(encoder_factory);
    kodo_coder_t* decoder = kodo_factory_new_decoder(decoder_factory);

    //uint8_t* payload = malloc(encoder->payload_size() * sizeof(uint8_t));

    while(!kodo_is_complete(decoder))
    {

    }
  


    return 0;
}
