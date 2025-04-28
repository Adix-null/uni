#ifndef COMMA_DECORATOR_HPP
#define COMMA_DECORATOR_HPP

#include "Decorator.hpp"
#include <string>

class CommaDecorator : public Decorator
{
public:
    CommaDecorator(Component *c);
    std::string process(const std::string &text) override;
    int countMistakes(const std::string &text) override;
};

#endif