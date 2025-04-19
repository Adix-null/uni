#ifndef INDENTATION_DECORATOR_HPP
#define INDENTATION_DECORATOR_HPP

#include <regex>
#include "Decorator.hpp"

class IndentationDecorator : public Decorator
{
public:
    IndentationDecorator(Component *c) : Decorator(c) {}

    std::string process(const std::string &text) override
    {
        std::string input = component->process(text);

        // indent every newline

        return input;
    }
};

#endif