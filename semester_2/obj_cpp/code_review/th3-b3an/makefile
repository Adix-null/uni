# make tests for testst
# make demo for demo

CXX = g++
CXXFLAGS = -std=c++14
RM = rm -f
TARGET_DEMO = demo
TARGET_TESTS = tests
OBJS_COMMON = Margherita.o PizzaDecorator.o CheeseBurstDecorator.o SpiceDecorator.o Exceptions.o

all: $(TARGET_DEMO)

$(TARGET_DEMO): demo.o $(OBJS_COMMON)
	$(CXX) $(CXXFLAGS) -o $(TARGET_DEMO) demo.o $(OBJS_COMMON)

$(TARGET_TESTS): tests.o $(OBJS_COMMON) StuffedCrustDecorator.o
	$(CXX) $(CXXFLAGS) -o $(TARGET_TESTS) tests.o $(OBJS_COMMON) StuffedCrustDecorator.o

demo.o: demo.cpp headers.h
	$(CXX) $(CXXFLAGS) -c demo.cpp

tests.o: tests.cpp headers.h
	$(CXX) $(CXXFLAGS) -c tests.cpp

Margherita.o: Margherita.cpp headers.h
	$(CXX) $(CXXFLAGS) -c Margherita.cpp

PizzaDecorator.o: PizzaDecorator.cpp headers.h
	$(CXX) $(CXXFLAGS) -c PizzaDecorator.cpp

CheeseBurstDecorator.o: CheeseBurstDecorator.cpp headers.h
	$(CXX) $(CXXFLAGS) -c CheeseBurstDecorator.cpp

SpiceDecorator.o: SpiceDecorator.cpp headers.h
	$(CXX) $(CXXFLAGS) -c SpiceDecorator.cpp

StuffedCrustDecorator.o: StuffedCrustDecorator.cpp headers.h
	$(CXX) $(CXXFLAGS) -c StuffedCrustDecorator.cpp

Exceptions.o: Exceptions.cpp headers.h
	$(CXX) $(CXXFLAGS) -c Exceptions.cpp

clean:
	$(RM) *.o $(TARGET_DEMO) $(TARGET_TESTS)
