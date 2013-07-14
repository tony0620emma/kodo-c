About
-----
In this folder you will find an example Makefile for building
and using the Kodo C bindings. The Makefile can be used in
cases where you wish to build the Kodo C bindings without using
the provided Waf build scripts.

To use the Makefile you might have to update the variables to
according to your directory layout and build system.

The Makefile builds two targets:
1. The ``libckodo.a`` static library containing the Kodo C bindings.
2. The ``encode_decode_example`` binary which is a C application provided
   in the examples folder demonstrating the use of the bindings API.



