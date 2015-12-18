//
//  ViewController.m
//  kodoc-ios-demo
//
//  Created by Steinwurf on 22/01/15.
//  Copyright (c) 2015 Steinwurf. All rights reserved.
//

#include <kodoc/kodoc.h>
#import "ViewController.h"


@interface ViewController ()


@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.info_label.text = @"";
    self.counter = 0;
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)start:(id)sender
{
    // Seed random number generator to produce different results every time
    srand((uint32_t)time(NULL));

    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 42;
    uint32_t max_symbol_size = 160;

    // Select the coding to use
    int32_t code_type = kodo_full_vector;

    // Select the finite field
    int32_t finite_field = kodo_binary;

    // Create the factories
    kodo_factory_t encoder_factory =
    kodo_new_encoder_factory(code_type, finite_field,
                             max_symbols, max_symbol_size);

    kodo_factory_t decoder_factory =
    kodo_new_decoder_factory(code_type, finite_field,
                             max_symbols, max_symbol_size);

    // Create the coders
    kodo_coder_t encoder = kodo_factory_build_coder(encoder_factory);
    kodo_coder_t decoder = kodo_factory_build_coder(decoder_factory);

    // Generate the data
    uint32_t payload_size = kodo_payload_size(encoder);
    uint8_t* payload = (uint8_t*) malloc(payload_size);

    uint32_t block_size = kodo_block_size(encoder);
    uint8_t* data_in = (uint8_t*) malloc(block_size);
    uint8_t* data_out = (uint8_t*) malloc(block_size);

    uint32_t i = 0;
    for(; i < block_size; ++i)
        data_in[i] = rand() % 256;

    kodo_set_const_symbols(encoder, data_in, block_size);
    kodo_set_mutable_symbols(decoder, data_out, block_size);

    kodo_set_systematic_off(encoder);

    // Run the decoding
    while (!kodo_is_complete(decoder))
    {
        kodo_write_payload(encoder, payload);
        kodo_read_payload(decoder, payload);
    }

    // Check if the decoding was successful
    uint8_t success = 0;
    if (memcmp(data_in, data_out, block_size) == 0)
        success = 1;

    // Clean up
    free(data_in);
    free(data_out);
    free(payload);

    kodo_delete_coder(encoder);
    kodo_delete_coder(decoder);

    kodo_delete_factory(encoder_factory);
    kodo_delete_factory(decoder_factory);

    if (success)
    {
        self.info_label.text =
            [NSString stringWithFormat: @"Test succeeded: %d", self.counter];
    }
    else
    {
        self.info_label.text =
            [NSString stringWithFormat: @"Test failed: %d", self.counter];
    }
    self.counter++;
}

@end
