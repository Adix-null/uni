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
        std::string input = component->process(text);
        std::string result;
        bool capitalizeNext = true;

        for (char ch : input)
        {
            if (std::isspace(static_cast<unsigned char>(ch)))
            {
                capitalizeNext = true;
                result += ch;
            }
            else if (capitalizeNext && std::isalpha(static_cast<unsigned char>(ch)))
            {
                result += std::toupper(static_cast<unsigned char>(ch));
                capitalizeNext = false;
            }
            else
            {
                result += ch;
                capitalizeNext = false;
            }
        }

        return result;
    }
};

#endif
