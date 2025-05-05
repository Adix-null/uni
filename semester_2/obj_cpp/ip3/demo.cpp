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