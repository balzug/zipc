# Compiler
CXX = g++

# Compilation flags
CXXFLAGS = -Wall -fPIC -g -O0 # Enable all warnings and generate position-independent code

# Linking flags
LIB_LDFLAGS = -shared   # Create a shared library

# Source files
LIB_SRCS = zipc.cpp
APP_SRCS = app.cpp

# Object files
LIB_OBJS = $(LIB_SRCS:.cpp=.o)

# Output shared library 
LIB_TARGET = libzipc.so

# App object
APP_OBJS = $(APP_SRCS:.cpp=.o)

# App binary
APP_TARGET = app

# Default target
all: $(LIB_TARGET) $(APP_TARGET)

# Rule to build the shared library
$(LIB_TARGET): $(LIB_OBJS)
	$(CXX) $(LIB_LDFLAGS) -o $@ $^

# Rule to build app binary
$(APP_TARGET): $(APP_OBJS)
	$(CXX) -o $@ $^ -lzipc -L.

# Rule to compile .cpp files into .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(LIB_OBJS) $(LIB_TARGET)
	rm -f $(APP_OBJS) $(APP_TARGET)

