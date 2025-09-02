#include <iostream>
#include <fstream>
#include <sstream>

#include "ConcreteComponent.hpp"
#include "CapitalizeDecorator.hpp"
#include "CommaDecorator.hpp"
#include "IndentationDecorator.hpp"
#include "Exception.hpp"

// Formatter
// Text formatter - implements decorator pattern. Base classes for definitions and managing components, decorators implement the logic and transform text in a specific way(e.g. lowercase, trim). Exception class for any errors.
// Component defines the structure of the text processor, the Decorator class is a base class for all decorators and ConcreteComponent is the main class that various decorators attach to.

// To use the project, go to the containing folder in the terminal and run
//```make``` to transform a file
//```make test``` to run the tests
//```make clean``` to remove generated temporary files

// The missing feature is the IndentationDecorator class that indents every newline with a tab. The structure should be the same as CapitalizeDecorator and CommaDecorator, returning a new string with the formatted result and counting mistakes. The countMistakes function should return the amount of newlines where a tab is needed, in the example below, 3. You also need to create an hpp file for the IndentationDecorator class.

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
        return -1;
    }

    std::stringstream buffer;
    buffer << input.rdbuf();

    // Polimorfizmas: Skirtingos išvestinės klasės skirtingai implementuoja tą patį bazinės klasės metodą. Decorator - bazinė klasė, su konstruktoriumi ir dviem vitualiais metodais, countMistakes ir process. Atskiros išvestinės klasės - CapitalizeDecorator, CommaDecorator šiuos metodus implementuoja skirtingai. Eilutės konkrečiuose dekoratorių failuose su `override` demonstruoja polimorfizmą.
    std::unique_ptr<Component> formatter =
        std::make_unique<IndentationDecorator>(
            std::make_unique<CommaDecorator>(
                std::make_unique<CapitalizeDecorator>(
                    std::make_unique<ConcreteComponent>())));

    output << "Mistake count: " << formatter->countMistakes(buffer.str()) << "\n";
    output << formatter->process(buffer.str());

    input.close();
    output.close();

    return 0;
}