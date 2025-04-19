#ifndef PUNCTUATION_DECORATOR_HPP
#define PUNCTUATION_DECORATOR_HPP

#include "Decorator.hpp"

class PunctuationDecorator : public Decorator
{
public:
    PunctuationDecorator(Component *c) : Decorator(c) {}

    std::string process(const std::string &text) override
    {
        std::string result = component->process(text);
        // if (!result.empty() && result.back() != '.')
        //{
        result += '.';
        //}
        return result;
    }
};

#endif
