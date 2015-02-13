#!/bin/bash

# Paths
ANDROID_NDK=~/toolchains/arm-linux-androideabi-4.8/arm-linux-androideabi/bin/
KODOC_INCLUDE=../../../src
BUILD=./build

# clean up
rm -rf $BUILD

# create build folder
mkdir $BUILD

# create object file
$ANDROID_NDK/gcc -x c -c -fpic -Wall -I$KODOC_INCLUDE dummy.c -o $BUILD/dummy.o

# create a shared library from the object file
$ANDROID_NDK/gcc -shared $BUILD/dummy.o -o $BUILD/libdummy.so
