#!/bin/bash

DEPS=/home/jeppe/git/kodo-c-bindings/bundle_dependencies/
FIFI=fifi-f85dcd/15.0.0/src
SAK=sak-2baed8/13.0.0/src
RECYCLE=recycle-fa0f6e/1.1.1/src
PLATFORM=platform-e774c1/1.2.1/src
BOOST=boost-6990ca/1.8.1
KODO=kodo-f3a9b9/21.0.0/src
CPUID=cpuid-a4173a/3.2.1/src

KODOC=/home/jeppe/git/kodo-c-bindings/src

BUILD_DIR=/home/jeppe/git/kodo-c-bindings/build/linux

rm -f dummy.o libdummy.a

echo
echo "######## Compiling dummy object file (dummy.o) ########"

g++ -x c -c -Wall \
-I$DEPS$FIFI \
-I$DEPS$SAK \
-I$DEPS$RECYCLE \
-I$DEPS$BOOST \
-I$DEPS$PLATFORM \
-I$DEPS$KODO \
-I$DEPS$FIFI \
-I$DEPS$CPUID \
-I$KODOC \
-L$BUILD_DIR \
-L. \
-o dummy.o \
dummy_project/src/dummy/dummy.c \
-lkodoc_static


echo "######## Archiving ########"


ar rcs libdummy.a dummy.o

DUMMY=/home/jeppe/git/kodo-c-bindings/examples/including_kodo/dummy_project/src

echo "######## Compiling main.c to program #######"

g++ -x c -static -Wall \
-I$DEPS$FIFI \
-I$DEPS$SAK \
-I$DEPS$RECYCLE \
-I$DEPS$BOOST \
-I$DEPS$PLATFORM \
-I$DEPS$KODO \
-I$DEPS$FIFI \
-I$DEPS$CPUID \
-I$DUMMY \
-I$KODOC \
-I$DEPS$FIFI \
-L$BUILD_DIR \
-I$DEPS$FIFI \
-L. \
-o program \
desktop/main.c \
-ldummy \
-lkodoc_static \
