#!/bin/bash

# Paths
BUILD=./build
DUMMY_INCLUDE=../dummy_library/src
DUMMY_LIB=../dummy_library/build
KODO_C_LIBS=../../../installs

g++ -x c -static -Wall \
-I$DUMMY_INCLUDE \
-L$DUMMY_LIB \
-L$KODO_C_LIBS \
-o $BUILD/program \
main.c \
-ldummy \
-lkodoc_static \
-lfifi \
-lcpuid
