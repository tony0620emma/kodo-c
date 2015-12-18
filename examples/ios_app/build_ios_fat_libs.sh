#!/bin/bash

# Target architectures
ARCHS="i386 x86_64 armv7 armv7s arm64"

LIPO_ARGS_KODOC=""
LIPO_ARGS_FIFI=""
LIPO_ARGS_CPUID=""

for ARCH in $ARCHS; do
    LIPO_ARGS_FIFI+="/tmp/$ARCH/libfifi.a "
    LIPO_ARGS_CPUID+="/tmp/$ARCH/libcpuid.a "
    LIPO_ARGS_KODOC+="/tmp/$ARCH/libkodoc_static.a "
done

lipo -create $LIPO_ARGS_KODOC -output libkodoc_static.a
lipo -create $LIPO_ARGS_FIFI -output libfifi.a
lipo -create $LIPO_ARGS_CPUID -output libcpuid.a

echo "######## Created fat static libs including $ARCHS:"
echo $(du -h libkodoc_static.a) $(lipo -info libkodoc_static.a)
echo $(du -h libfifi.a) $(lipo -info libfifi.a)
echo $(du -h libcpuid.a) $(lipo -info libcpuid.a)
echo "######## Finished."
