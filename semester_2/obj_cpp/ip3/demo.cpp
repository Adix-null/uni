#include <iostream>
#include <fstream>
#include <sstream>

#include "ConcreteComponent.hpp"
#include "CapitalizeDecorator.hpp"
#include "PunctuationDecorator.hpp"

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    std::stringstream buffer;
    buffer << input.rdbuf();

    Component *formatter = new PunctuationDecorator(
        new CapitalizeDecorator(
            new ConcreteComponent()));

    std::string result = formatter->process(buffer.str());

    output << result;

    return 0;
}