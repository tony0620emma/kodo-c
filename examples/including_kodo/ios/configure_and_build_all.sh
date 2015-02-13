#!/bin/bash

DIRECTORY=$PWD

cd ../../../

for ARCH in i386 x86_64 armv7 armv7s arm64; do
    python waf configure --options=cxx_mkspec=cxx_ios70_apple_llvm60_$ARCH
    python waf build
    python waf install --options=install_path=/tmp/$ARCH/,install_static_libs
done

cd $DIRECTORY
