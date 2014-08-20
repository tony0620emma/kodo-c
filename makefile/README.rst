Readme
------

This folder contains an example Makefile for building and using the
Kodo C bindings. The Makefile can be useful if you wish to build the
Kodo C bindings without the provided Waf build scripts.

To use the Makefile, you might have to update the variables
according to your directory layout and build system.

To change the compiler, just set the CC and CXX environment variables
to the desired compilers. Note that ``gcc/g++`` is the default compiler on
Linux, and ``clang`` is the default compiler on Mac OSX.


The Makefile builds 6 targets:

1. The ``libckodo.a`` static library containing the Kodo C bindings.
2. The ``libckodo.so`` shared library containing the Kodo C bindings.
3. The ``encode_decode_example`` binary which is a C application provided
   in the examples folder demonstrating the use of the bindings API.
4. The ``encode_decode_on_the_fly`` binary (C example application)
5. The ``udp_sender`` binary (C example application for sending encoded packets)
6. The ``udp_receiver`` binary (C example application for receiving encoded
   packets)
