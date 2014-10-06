# Makefile for building the Kodo C bindings and the associated examples

# Note that the paths to the libraries depend on your specific machine and will
# need to be updated.

# By default, we assume that the required libraries are cloned side-by-side with
# the kodo-c folder.
# You can clone the projects like this:
# git clone https://github.com/steinwurf/sak.git
# git clone https://github.com/steinwurf/fifi.git
# git clone https://github.com/steinwurf/platform.git
# git clone https://github.com/steinwurf/cpuid.git
# git clone https://github.com/steinwurf/boost.git
# git clone https://github.com/steinwurf/kodo.git
# git clone https://github.com/steinwurf/kodo-c.git
#
# Then build the C bindings with this makefile:
# cd kodo-c/examples/sample_makefile
# make

UNAME_S := $(shell uname -s)

# Specify the path to every dependency

# The include path to the kodo sources
KODO_DIR ?= ../../../kodo/src

# The include path to the sak sources
SAK_DIR ?= ../../../sak/src

# The include path to the fifi sources
FIFI_DIR ?= ../../../fifi/src

# Fifi is a library but instead of compiling the library we just
# compile all the .cpp files. Note that compiling Fifi this way will
# disable all hardware SIMD accelerations.
FIFI_CPP_FILES := $(wildcard $(FIFI_DIR)/fifi/*.cpp)

# The include path to the boost sources
BOOST_DIR ?= ../../../boost

# The include path for the platform sources
PLATFORM_DIR ?= ../../../platform/src

# The include path for the cpuid sources
CPUID_DIR ?= ../../../cpuid/src

# cpuid is also a library but instead of compiling the library we just
# compile all the .cpp files.
CPUID_CPP_FILES := $(wildcard $(CPUID_DIR)/cpuid/*.cpp)

# Set C++ flags for the library
INCLUDES = -I$(BOOST_DIR) -I$(SAK_DIR) -I$(FIFI_DIR) -I$(KODO_DIR) \
           -I$(PLATFORM_DIR) -I$(CPUID_DIR) -I ../../src

CXXFLAGS = -std=c++0x -O2 -ftree-vectorize

# Choose default compiler based on the OS
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
        CXXFLAGS = -std=c++0x -O2 -stdlib=libc++ -lc++
    endif
    ifneq (,$(findstring c++,$(CXX)))
        CXXFLAGS = -std=c++0x -O2 -stdlib=libc++ -lc++
    endif
endif

# Set C++ flags for Android cross-compiler (required for cstdint and boost)
ifneq (,$(findstring android,$(CXX)))
    CXXFLAGS = -std=gnu++0x -s -O2 -ftree-vectorize \
               -DANDROID -DBOOST_ALL_NO_LIB=1 -D__GLIBC__ \
               -D_GLIBCXX_USE_WCHAR_T -D_GLIBCXX_USE_C99_STDINT_TR1
endif

# Specify C bindings source files
CKODO_SRC = ../../src/ckodo/ckodo.cpp

# Point to the source file of our selected example
EXAMPLE_SRC = ../encode_decode_simple/encode_decode_simple.c

TARGET ?= encode_decode_simple

CPP_SOURCES = $(CPUID_CPP_FILES) $(FIFI_CPP_FILES) $(CKODO_SRC) $(EXAMPLE_SRC)

# Invoke the compiler
.PHONY: all
all:
	$(CXX) $(CPP_SOURCES) -o $(TARGET) $(CXXFLAGS) $(INCLUDES)

.PHONY: clean
clean:
	rm -f $(TARGET)
