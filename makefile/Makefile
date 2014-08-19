# Makefile for building the Kodo C bindings and the associated examples

# Note that the paths to the libraries depend
# on your specific machine and will need to be updated.

# By default, we assume that the required libraries (sak, fifi, kodo and boost)
# are cloned side-by-side with the kodo-c-bindings folder.
# You can clone the projects like this:
# git clone https://github.com/steinwurf/sak.git
# git clone https://github.com/steinwurf/fifi.git
# git clone https://github.com/steinwurf/external-boost-light.git
# git clone https://github.com/steinwurf/kodo.git
# git clone https://github.com/steinwurf/kodo-c-bindings.git
# Then build the C bindings with this makefile:
# cd kodo-c-bindings/makefile
# make

UNAME_S := $(shell uname -s)

# Specify the path to every dependency

# The include path to the kodo sources
KODO_DIR ?= ../../kodo/src

# The include path to the sak sources
SAK_DIR ?= ../../sak/src

# The include path to the fifi sources
FIFI_DIR ?= ../../fifi/src

# The include path to the boost sources
BOOST_DIR ?= ../../external-boost-light

# Set C++ flags for the library
INCLUDES = -I $(BOOST_DIR) -I $(SAK_DIR) -I $(FIFI_DIR) -I $(KODO_DIR)
CXXFLAGS = -std=c++0x -fPIC -O2 -ftree-vectorize
SHAREDLIB-FLAGS = -shared -s
# Produce self-contained shared library (only if stdc++ was compiled with -fPIC)
#SHAREDLIB-FLAGS += -static-libgcc -static-libstdc++

# Set C flags for the examples
CINCLUDES= -I ../src
CFLAGS = -O2 -ftree-vectorize
# Static linking with the C++ standard library (for embedded platforms)
LINKFLAGS = -s -static-libstdc++
CLIBS = -Wl,-Bstatic -L. -lckodo
# Dynamic linking with the C++ standard library (where the stdc++ is available)
#CLIBS = -Wl,-Bstatic -L. -lckodo -Wl,-Bdynamic -lstdc++

# Specify the archiver
AR ?= ar
ARFLAGS = rcs

# Choose default C compiler based on the OS
ifeq ($(CC),)
    ifeq ($(UNAME_S),Linux)
        CC = gcc
    endif
    ifeq ($(UNAME_S),Darwin)
        CC = clang
    endif
endif

# Choose default C++ compiler based on the OS
ifeq ($(CXX),)
    ifeq ($(UNAME_S),Linux)
        CXX = g++
    endif
    ifeq ($(UNAME_S),Darwin)
        CXX = clang++
    endif
endif

# Set C++ flags for clang on Mac OSX
ifeq ($(UNAME_S),Darwin)
    ifneq (,$(findstring clang++,$(CXX)))
        CXXFLAGS = -std=c++0x -fPIC -O2 -stdlib=libc++
        SHAREDLIB-FLAGS = -shared -lc++
        LINKFLAGS =
    endif
    ifneq (,$(findstring c++,$(CXX)))
        CXXFLAGS = -std=c++0x -fPIC -O2 -stdlib=libc++
        SHAREDLIB-FLAGS = -shared -lc++
        LINKFLAGS =
    endif
    CLIBS = -L. -lckodo
endif


# Put the created object files in OBJDIR
OBJDIR ?= obj
$(shell   mkdir -p $(OBJDIR))

# The ckodo static library
STATICLIB = libckodo.a

# The ckodo shared library
SHAREDLIB = libckodo.so
LIBRARY-SRC = ../src/ckodo/ckodo.cpp


# The examples are statically linked with libckodo.a
EXAMPLE1 = encode_decode_simple
EXAMPLE1-DIR ?= ../examples/encode_decode_simple
EXAMPLE1-SRC = $(EXAMPLE1-DIR)/encode_decode_simple.c

EXAMPLE2 = encode_decode_on_the_fly
EXAMPLE2-DIR ?= ../examples/encode_decode_on_the_fly
EXAMPLE2-SRC = $(EXAMPLE2-DIR)/encode_decode_on_the_fly.c

EXAMPLE3A = udp_sender
EXAMPLE3B = udp_receiver
EXAMPLE3-DIR ?= ../examples/udp_sender_receiver
EXAMPLE3A-SRC = $(EXAMPLE3-DIR)/udp_sender.c
EXAMPLE3B-SRC = $(EXAMPLE3-DIR)/udp_receiver.c

.PHONY: all
all: $(STATICLIB) $(SHAREDLIB) $(EXAMPLE1) $(EXAMPLE2) $(EXAMPLE3A) $(EXAMPLE3B)

# Build the static library
$(STATICLIB): $(OBJDIR)/ckodo.o
	$(AR) $(ARFLAGS) $@ $^

# Build the shared library
$(SHAREDLIB): $(OBJDIR)/ckodo.o
	$(CXX) $< -o $@ $(SHAREDLIB-FLAGS)

$(OBJDIR)/ckodo.o: $(LIBRARY-SRC)
	$(CXX) $< -o $@ -c $(CXXFLAGS) $(INCLUDES)

# Build the examples
$(EXAMPLE1): $(OBJDIR)/$(EXAMPLE1).o $(STATICLIB)
	$(CXX) $(LINKFLAGS) $< -o $@ $(CLIBS)

$(OBJDIR)/$(EXAMPLE1).o: $(EXAMPLE1-SRC)
	$(CC) $< -o $@ -c $(CFLAGS) $(CINCLUDES)

$(EXAMPLE2): $(OBJDIR)/$(EXAMPLE2).o $(STATICLIB)
	$(CXX) $(LINKFLAGS) $< -o $@ $(CLIBS)

$(OBJDIR)/$(EXAMPLE2).o: $(EXAMPLE2-SRC)
	$(CC) $< -o $@ -c $(CFLAGS) $(CINCLUDES)

$(EXAMPLE3A): $(OBJDIR)/$(EXAMPLE3A).o $(STATICLIB)
	$(CXX) $(LINKFLAGS) $< -o $@ $(CLIBS)

$(OBJDIR)/$(EXAMPLE3A).o: $(EXAMPLE3A-SRC)
	$(CC) $< -o $@ -c $(CFLAGS) $(CINCLUDES)

$(EXAMPLE3B): $(OBJDIR)/$(EXAMPLE3B).o $(STATICLIB)
	$(CXX) $(LINKFLAGS) $< -o $@ $(CLIBS)

$(OBJDIR)/$(EXAMPLE3B).o: $(EXAMPLE3B-SRC)
	$(CC) $< -o $@ -c $(CFLAGS) $(CINCLUDES)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ $(STATICLIB) $(SHAREDLIB) \
		$(EXAMPLE1) $(EXAMPLE2) $(EXAMPLE3A) $(EXAMPLE3B)
