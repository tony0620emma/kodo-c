#!/bin/bash

# INCLUDEPATHS
KODOC=../../../src
DUMMY=../dummy_library/src

# STATIC LIB PATH
INSTALLS=../../../installs

# Build Target Architectures
ARCHS="i386 armv7 armv7s arm64"

LIPO_ARGS_DUMMY=""
LIPO_ARGS_FIFI=""
LIPO_ARGS_CPUID=""

for ARCH in $ARCHS; do
    # remove old stuff if present
    rm -f dummy.o libdummy.a program

    echo
    echo "######## Compiling dummy object file (dummy.o) for arch $ARCH .."

    SDKTYPE=iPhoneOS
    IOSTARGET=iphoneos-version-min=7.0

    if [ "$ARCH" == "i386" ]; then
	SDKTYPE=iPhoneSimulator
	IOSTARGET=ios-simulator-version-min=7.0
    fi
    
    # Specifiy the sysroot based on sdk type. This is the default sdk paths.
    SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/$SDKTYPE.platform/Developer/SDKs/$SDKTYPE.sdk

    g++ -x c -c -Wall \
	-target $ARCH-apple-ios7.0.0 \
	-isysroot $SYSROOT \
	-m$IOSTARGET \
	-I$KODOC \
	-o dummy.o \
	$DUMMY/dummy/dummy.c \

	echo "######## Archiving.."

    # create static library from object file
    ar rcs libdummy_$ARCH.a dummy.o

    # make sure we dont use dummy.o file
    rm -f dummy.o

    echo "######## Compiling main.c to program.."

    g++ -x c -Wall \
	-lc++ \
	-target $ARCH-apple-ios7.0.0 \
	-isysroot $SYSROOT \
	-m$IOSTARGET \
	-I$DUMMY \
	-I$KODOC \
	-L. \
	-L/tmp/$ARCH \
	-o program_$ARCH \
	../desktop/main.c \
	-ldummy_$ARCH \
	-lkodoc_static \
	-lfifi \
	-lcpuid

    echo "######## We do not run program here, merely verify that is was compiled:"

    du -h program_$ARCH

    rm -f ./program_$ARCH

    echo "######## Finished with arch $ARCH .."

    LIPO_ARGS_DUMMY+="libdummy_$ARCH.a "
    LIPO_ARGS_FIFI+="/tmp/$ARCH/libfifi.a "
    LIPO_ARGS_CPUID+="/tmp/$ARCH/libcpuid.a "
done

lipo -create $LIPO_ARGS_DUMMY -output libdummy.a
rm -f $LIPO_ARGS_DUMMY

lipo -create $LIPO_ARGS_FIFI -output libfifi.a
lipo -create $LIPO_ARGS_CPUID -output libcpuid.a

echo "######## Created fat static libs with archs $ARCHS:"
du -h libdummy.a
du -h libfifi.a
du -h libcpuid.a
echo "######## Finished."
