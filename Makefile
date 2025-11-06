# Compiler
CXX = g++

# Compilation flags
CXXFLAGS = -Wall -fPIC  # Enable all warnings and generate position-independent code

# Linking flags
LDFLAGS = -shared       # Create a shared library

# Source files
LIB_SRCS = zipc.cpp

# Object files
LIB_OBJS = $(LIB_SRCS:.cpp=.o)

# Output shared library 
LIB_TARGET = libzipc.so

# Default target
all: $(LIB_TARGET)

# Rule to build the shared library
$(LIB_TARGET): $(LIB_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Rule to compile .cpp files into .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(LIB_OBJS) $(LIB_TARGET)

