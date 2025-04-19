#ifndef CAPITALIZE_DECORATOR_HPP
#define CAPITALIZE_DECORATOR_HPP

#include "Decorator.hpp"
#include <cctype>

class CapitalizeDecorator : public Decorator
{
public:
    CapitalizeDecorator(Component *c) : Decorator(c) {}

    std::string process(const std::string &text) override
    {
        std::string result = component->process(text);
        for (char &ch : result)
        {
            ch = std::toupper(static_cast<unsigned char>(ch));
        }
        return result;
    }
};

#endif
