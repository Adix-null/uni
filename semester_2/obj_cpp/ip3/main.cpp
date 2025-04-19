#include <iostream>
#include <fstream>
#include <sstream>

#include "ConcreteComponent.hpp"
#include "CapitalizeDecorator.hpp"
#include "PunctuationDecorator.hpp"
#include "Exception.hpp"

int main()
{
    std::ifstream input;
    std::ofstream output;

    FILE *file;
    try
    {
        input = std::ifstream("input.txt");
        output = std::ofstream("output.txt");
    }
    catch (const FileException &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::stringstream buffer;
    buffer << input.rdbuf();

    Component *formatter =
        new PunctuationDecorator(
            new CapitalizeDecorator(
                new ConcreteComponent()));

    std::string result = formatter->process(buffer.str());

    output << result;

    return 0;
}