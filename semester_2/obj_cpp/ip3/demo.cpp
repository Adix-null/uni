#include <iostream>
#include <fstream>
#include <sstream>

#include "ConcreteComponent.hpp"
#include "CapitalizeDecorator.hpp"
#include "CommaDecorator.hpp"
#include "IndentationDecorator.hpp"
#include "Exception.hpp"

int main()
{
    std::ifstream input;
    std::ofstream output;

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

    // Polimorfizmas: Component* nurodo išvestinį objektą
    Component *formatter =
        new CommaDecorator(
            new CapitalizeDecorator(
                new ConcreteComponent()));

    output << "Mistake count: " << formatter->countMistakes(buffer.str()) << "\n";
    output << formatter->process(buffer.str());

    return 0;
}