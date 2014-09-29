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

The Makefile builds the ``encode_decode_simple`` binary which is a simple
C application provided to demonstrate the usage of the C API.
