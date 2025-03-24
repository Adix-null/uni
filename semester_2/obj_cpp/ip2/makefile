CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Files and Targets
SRC = func.cpp demo.cpp test.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = demo
testEXEC = test

# Default target (build everything)
all: build

# Build targets
build: $(EXEC)

$(EXEC): func.o demo.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test_build: $(testEXEC)

$(testEXEC): func.o test.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run targets
run: build
	./$(EXEC)

test_run: test_build
	./$(testEXEC)

# Combined build and run
build_run: build run

test_build_run: test_build test_run

# Object files
%.o: %.cpp func.hpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean
clean:
	rm -f $(OBJ) $(EXEC) $(testEXEC)