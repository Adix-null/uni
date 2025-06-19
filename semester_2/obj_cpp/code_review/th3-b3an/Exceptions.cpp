#include "headers.h"

PizzaCustomizationException::PizzaCustomizationException(const std::string& message) : msg_(message) {}

const char* PizzaCustomizationException::what() const noexcept {
    return msg_.c_str();
}

CheeseDecoratorException::CheeseDecoratorException(const std::string& msg)
    : PizzaCustomizationException("CheeseDecorator: " + msg) {}

SpiceDecoratorException::SpiceDecoratorException(const std::string& msg)
    : PizzaCustomizationException("SpiceDecorator: " + msg) {}

StuffedDecoratorException::StuffedDecoratorException(const std::string& msg)
    : PizzaCustomizationException("StuffedDecorator: " + msg) {}