# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -Wall -Wextra -O2
# Output executable
TARGET = output

# Source files
SRCS = main.cpp func.cpp
# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compiling .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Run the compiled program
run: all
	./$(TARGET)