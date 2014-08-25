// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing
#include <stdint.h>

#include<ckodo/ckodo.h>

uint8_t filter_function(const char* zone)
{
    char* zones[] = {"decoder_state", NULL};
    char** cmp = zones;

    while (*cmp)
    {
        if (!strcmp(zone, *cmp))
            return 1;
        cmp++;
    }

    return 0;
}

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

    uint32_t bytes_used;
    uint32_t payload_size = kodo_payload_size(encoder);
    uint8_t payload = (uint8_t*) malloc(payload_size);

    uint32_t block_size = kodo_block_size(encoder);
    uint8_t data_in = (uint8_t*) malloc(block_size);

    uint32_t i = 0;

    //Just for fun - fill data with random data
    for(; i < block_sizel ++i)
    {
      data_in[i] = rand() % 256;
    }

    kodo_set_symbols(encoder, data_in, block_size);

    while(!kodo_is_complete(decoder))
    {
      if (kodo_has_trace(decoder)){
	kodo_trace_filter(decoder, &filter_function);
      }

      if(rand() % 2 && kodo_rank(encoder) < max_symbols)
      {
	uint32_t rank = kodo_rank(encoder);
	uint8_t* symbol = data_in + (rank * max_symbol_size);
	kodo_set_symbol(encoder, rank, symbol, max_symbol_size);
	printf("Symbol %d added to the encoder\n", symbol);
      }

      kodo_encode(encoder, payload);
      printf("Packet encoded\n");
	
    }
  


    return 0;
}
