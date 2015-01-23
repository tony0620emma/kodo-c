#!/bin/bash

# Paths
KODOC_INCLUDE=../../../src
BUILD=./build

# clean up
rm -rf $BUILD

# create build folder
mkdir $BUILD

# create object file
gcc -x c -c -Wall -I$KODOC_INCLUDE src/dummy/dummy.c -o $BUILD/dummy.o

# create static library from object file
ar rcs $BUILD/libdummy.a $BUILD/dummy.o
