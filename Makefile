# CHAT GPT ROCKS

# Makefile for Tensor project

# Compiler settings
CXX := clang++
CXXFLAGS := -g -Wall -fPIC -std=c++17

# Directories
SRCDIR := src
BUILDDIR := build
LIBDIR := $(BUILDDIR)/lib
BINDIR := $(BUILDDIR)/bin

# Target files
LIBTARGET := $(LIBDIR)/libTensor.so
BINTARGET := $(BINDIR)/run

# Source and Object files
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(LIBDIR)/%.o)

# Optional main program
MAIN := run.cpp
MAINOBJ := $(BINDIR)/run.o

.PHONY: all clean

all: $(LIBTARGET) $(BINTARGET)

# Compile the Tensor library
$(LIBTARGET): $(OBJS)
	@mkdir -p $(LIBDIR)
	$(CXX) $(CXXFLAGS) -shared -o $@ $^

# Compile the objects for the library
$(LIBDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(LIBDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile the main program if it exists
$(BINTARGET): $(MAINOBJ)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(LIBDIR) -lTensor -Wl,-rpath,$(LIBDIR)

$(MAINOBJ): $(MAIN)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)
