#ifndef CAPITALIZE_DECORATOR_HPP
#define CAPITALIZE_DECORATOR_HPP

#include "Decorator.hpp"
#include <string>

class CapitalizeDecorator : public Decorator
{
public:
    explicit CapitalizeDecorator(std::unique_ptr<Component> c);
    std::string process(const std::string &text) override;
    int countMistakes(const std::string &text) override;
};

#endif