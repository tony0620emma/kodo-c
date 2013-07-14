# Build a ckodo static library
STATICLIB = libckodo.a
STATICLIBSRC = ../src/ckodo/ckodo.cpp

# Build an example to be statically linked with libckodo.a
EXAMPLE = encode_decode_simple
EXAMPLESRC = ../examples/encode_decode_simple/encode_decode_simple.c

# Specify the compilers
AR = ar
CC = gcc-4.6
CXX = g++-4.6

# Put the created object files in OBJDIR
OBJDIR = obj
$(shell   mkdir -p $(OBJDIR))

# Specify the path to every dependency in the standalone package

# The include path to the boost sources
BOOST_DIR = ../bundle_dependencies/boost-91e411/1.0.0

# The include path to the sak sources
SAK_DIR = ../bundle_dependencies/sak-2baed8/10.2.0/src

# The include path to the fifi sources
FIFI_DIR = ../bundle_dependencies/fifi-f85dcd/9.1.0/src

# The include path to the kodo sources
KODO_DIR = ../bundle_dependencies/kodo-f3a9b9/11.1.0/src

# Flags for C++ compiler
INCLUDES = -I $(BOOST_DIR) -I $(SAK_DIR) -I $(FIFI_DIR) -I $(KODO_DIR)
CXXFLAGS = --std=c++0x -O2 -ftree-vectorize
ARFLAGS = rcs

# Flags for C compiler
CCFLAGS=-I ../src
LDFLAGS =
CCLIBS = -L. -lckodo -lstdc++

.PHONY: all
all: $(STATICLIB) $(EXAMPLE)

# Build the static library first
$(STATICLIB): $(OBJDIR)/ckodo.o
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/ckodo.o: $(STATICLIBSRC)
	$(CXX) $< -o $@ -c $(CXXFLAGS) $(INCLUDES)

# Build the example second
$(EXAMPLE): $(OBJDIR)/$(EXAMPLE).o $(STATICLIB)
	$(CC) $(LDFLAGS) $< $(CCLIBS) -o $@

$(OBJDIR)/$(EXAMPLE).o: $(EXAMPLESRC)
	$(CC) $< -o $@ -c $(CCFLAGS)


.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ $(STATICLIB) $(EXAMPLE)