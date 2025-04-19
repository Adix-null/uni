CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = demo.cpp
TEST_SRC = test.cpp
OBJS = ConcreteComponent.hpp CapitalizeDecorator.hpp CommaDecorator.hpp IndentationDecorator.hpp Component.hpp Decorator.hpp Exception.hpp

all: formatter

formatter: $(SRC) $(OBJS)
	$(CXX) $(CXXFLAGS) -o formatter $(SRC)
	./formatter

test: $(TEST_SRC) $(OBJS)
	$(CXX) $(CXXFLAGS) -o test_otp $(TEST_SRC)
	./test_otp

clean:
	rm -f *.o formatter  test_otp