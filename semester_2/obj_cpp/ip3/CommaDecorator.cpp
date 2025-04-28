#include "CommaDecorator.hpp"
#include <cctype>

CommaDecorator::CommaDecorator(Component *c) : Decorator(c) {}

std::string CommaDecorator::process(const std::string &text)
{
    std::string input = component->process(text);

    std::string result;
    size_t i = 0;
    while (i < input.size())
    {
        if (input[i] == ',')
        {
            // remove space before ,
            while (!result.empty() && result.back() == ' ')
            {
                result.pop_back();
            }

            result += ',';
            ++i;

            // remove space after ,
            while (i < input.size() && input[i] == ' ')
            {
                ++i;
            }

            result += ' ';
        }
        else
        {
            result += input[i];
            ++i;
        }
    }

    return result;
}

int CommaDecorator::countMistakes(const std::string &text)
{
    int mistakes = 0;

    for (size_t i = 0; i < text.size(); ++i)
    {
        if (text[i] == ',')
        {
            // Check for space before ,
            if (i > 0 && text[i - 1] == ' ')
            {
                mistakes++;
            }
            else
            {
                // Check for only one space after ,
                size_t j = i + 1;
                int spaceCount = 0;
                while (j < text.size() && text[j] == ' ')
                {
                    spaceCount++;
                    j++;
                }

                if (spaceCount != 1)
                {
                    mistakes++;
                }
            }
        }
    }

    return mistakes + component->countMistakes(text);
}