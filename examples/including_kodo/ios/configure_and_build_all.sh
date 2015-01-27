#!/bin/bash

DIRECTORY=$PWD

cd ../../../

for ARCH in i386 armv7 armv7s arm64; do
    python waf configure -p --options=cxx_mkspec=cxx_ios70_apple_llvm60_$ARCH --prefix=/tmp/$ARCH build install --options=install_path=/tmp/$ARCH/,install_static_libs
done

cd $DIRECTORY
