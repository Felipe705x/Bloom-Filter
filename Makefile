# Variables
CXX = g++
CXXFLAGS = -std=c++17 -I./include -Wall
LDFLAGS = 

# Directories
SRCDIR = source
HEADERSDIR = include
BUILDDIR = build
TARGET = $(BUILDDIR)/main

# Source and object files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Default rule
all: $(TARGET)

# Clean, compile and run the final target
run: clean all
	$(TARGET)

# Compile the final target and run it
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Rule to compile .o files from .cpp files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean compiled files
clean:
	rm -rf $(BUILDDIR)
	mkdir -p $(BUILDDIR)

# Phony targets
.PHONY: all clean