# Makefile for building the Kodo C bindings and the associated examples

# Note that the paths to the libraries depend on your specific machine and will
# need to be updated.

# By default, we assume that the required libraries are cloned side-by-side with
# the kodo-c-bindings folder.
# You can clone the projects like this:
# git clone https://github.com/steinwurf/sak.git
# git clone https://github.com/steinwurf/fifi.git
# git clone https://github.com/steinwurf/platform.git
# git clone https://github.com/steinwurf/cpuid.git
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

# Fifi is a library but instead of compiling the library we just
# compile all the .cpp files. Note that compiling Fifi this way will
# disable all hardware SIMD accelerations.
FIFI_CPP_FILES := $(wildcard $(FIFI_DIR)/fifi/*.cpp)

# The include path to the boost sources
BOOST_DIR ?= ../../external-boost-light

# The include path for the platform sources
PLATFORM_DIR ?= ../../platform/src

# The include path for the cpuid sources
CPUID_DIR ?= ../../cpuid/src

# cpuid is also a library but instead of compiling the library we just
# compile all the .cpp files.
CPUID_CPP_FILES := $(wildcard $(CPUID_DIR)/cpuid/*.cpp)

# Set C++ flags for the library
INCLUDES = -I$(BOOST_DIR) -I$(SAK_DIR) -I$(FIFI_DIR) -I$(KODO_DIR) \
           -I$(PLATFORM_DIR) -I$(CPUID_DIR)

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
SOURCES = ../src/ckodo/ckodo.cpp $(CPUID_CPP_FILES) $(FIFI_CPP_FILES)
OBJECTS = $(SOURCES:.cpp=.o)

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

EXAMPLE4 = sliding_window
EXAMPLE4-DIR ?= ../examples/sliding_window
EXAMPLE4-SRC = $(EXAMPLE4-DIR)/$(EXAMPLE4).c
.PHONY: all
all: $(STATICLIB) $(SHAREDLIB) $(EXAMPLE1) $(EXAMPLE2) $(EXAMPLE3A) $(EXAMPLE3B) 
#$(EXAMPLE4)

# Build the static library
$(STATICLIB): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

# Build the shared library
$(SHAREDLIB): $(OBJECTS)
	$(CXX) $< -o $@ $(SHAREDLIB-FLAGS)

.cpp.o: $(OBJDIR)/$(OBJECTS)
	$(CXX) $< -o $@ -c $(CXXFLAGS) $(INCLUDES)

# Build the examples
$(EXAMPLE1): $(OBJDIR)/$(EXAMPLE1).o $(STATICLIB)
	$(CXX)  $(LINKFLAGS) $< -o $@ $(CLIBS)

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

$(EXAMPLE4): $(OBJDIR)/$(EXAMPLE4).o $(STATICLIB)
	$(CXX) $(LINKFLAGS) $< -o $@ $(CLIBS)

$(OBJDIR)/$(EXAMPLE4).o: $(STATICLIB)
	$(CXX) $(LINKFLAGS) $< -o $@ $(CLIBS)


$.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ $(STATICLIB) $(SHAREDLIB) \
		$(EXAMPLE1) $(EXAMPLE2) $(EXAMPLE3A) $(EXAMPLE3B)
