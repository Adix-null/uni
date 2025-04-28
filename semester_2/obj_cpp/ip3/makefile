CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = demo.cpp
TEST_SRC = test.cpp
OBJS = ConcreteComponent.hpp CapitalizeDecorator.cpp CommaDecorator.cpp IndentationDecorator.cpp 

all: formatter

formatter: $(SRC) $(OBJS)
	$(CXX) $(CXXFLAGS) -o formatter $(SRC) $(OBJS)
	./formatter

test: $(TEST_SRC) $(OBJS)
	$(CXX) $(CXXFLAGS) -o test_otp $(TEST_SRC) $(OBJS)
	./test_otp

clean:
	rm -f *.o formatter test_otp