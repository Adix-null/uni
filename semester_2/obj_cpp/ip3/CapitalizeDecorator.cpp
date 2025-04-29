#include "CapitalizeDecorator.hpp"
#include <cctype>
#include <memory>

CapitalizeDecorator::CapitalizeDecorator(std::unique_ptr<Component> c)
    : Decorator(std::move(c)) {}

std::string CapitalizeDecorator::process(const std::string &text)
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

int CapitalizeDecorator::countMistakes(const std::string &text)
{
    int mistakes = 0;
    bool atWordStart = true;

    for (size_t i = 0; i < text.size(); ++i)
    {
        char ch = text[i];

        if (std::isalpha(static_cast<unsigned char>(ch)))
        {
            if (atWordStart)
            {
                if (!std::isupper(static_cast<unsigned char>(ch)))
                {
                    mistakes++;
                }
                atWordStart = false;
            }
        }
        else
        {
            atWordStart = true;
        }
    }

    return mistakes + component->countMistakes(text);
}