#!/bin/bash

# INCLUDEPATHS
KODOC=/home/jeppe/git/kodo-c-bindings/src
DUMMY=/home/jeppe/git/kodo-c-bindings/examples/including_kodo/dummy_project/src

# STATIC LIB PATH
INSTALLS=/home/jeppe/git/kodo-c-bindings/installs

# remove old stuff
rm -f dummy.o libdummy.a program

echo
echo "######## Compiling dummy object file (dummy.o).."

g++ -x c -c -Wall \
-I$KODOC \
-o dummy.o \
dummy_project/src/dummy/dummy.c \

echo "######## Archiving.."

# create static library from object file
ar rcs libdummy.a dummy.o

# make sure we dont use dummy.o file
rm -f dummy.o

echo "######## Compiling main.c to program.."

g++ -x c -static -Wall \
-I$DUMMY \
-I$KODOC \
-L. \
-L$INSTALLS \
-o program \
desktop/main.c \
-ldummy \
-lkodoc_static \
-lfifi \
-lcpuid

echo "######## Running program.."

./program

rm -f ./program

echo "######## Finished.."
echo # more space :)
