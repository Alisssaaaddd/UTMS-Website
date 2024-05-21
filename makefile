# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra -I./include #-fsanitize=address -fsanitize=undefined

# Linker flags (library paths)
LFLAGS = -L./files

# Directories
SRCDIR = src
OBJDIR = objects
BINDIR = .
EXECUTABLE = $(BINDIR)/utms.out
MEDIA_PATH = ./files/

# Source files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Default target: build the executable
all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(wildcard $(SRCDIR)/*.hpp)
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(MEDIA_PATH)

# Clean up object files and the executable
clean:
	rm -rf $(OBJDIR)/*.o $(EXECUTABLE)
