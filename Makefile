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
all: clean pre_compile $(TARGET) newline

# Clean, compile and run the final target
run: all
	@echo "Running the application..."
	@echo ""
	@echo ""
	@$(TARGET)

pre_compile:
	@echo "Compiling..."

newline:
	@echo ""

# Compile the final target and run it
$(TARGET): $(OBJECTS)
	@echo "Starting to link the executable..."
	@$(CXX) $(LDFLAGS) -o $@ $^
	@echo "Executable built. Cleaning up object files..."
	@rm -f $(OBJECTS)

# Rule to compile .o files from .cpp files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean compiled files
clean:
	@echo "Cleaning the build directory..."
	@rm -rf $(BUILDDIR)
	@mkdir -p $(BUILDDIR)

# Phony targets
.PHONY: all clean run pre_compile