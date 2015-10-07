#!/bin/bash

DIRECTORY=$PWD

cd ../../../

for ARCH in i386 x86_64 armv7 armv7s arm64; do
    python waf configure --cxx_mkspec=cxx_ios70_apple_llvm_$ARCH
    python waf build
    python waf install --install_path=/tmp/$ARCH/ --install_static_libs
done

cd $DIRECTORY
