#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>

#include "ConcreteComponent.hpp"
#include "CapitalizeDecorator.hpp"
#include "CommaDecorator.hpp"
#include "IndentationDecorator.hpp"
#include "Exception.hpp"

void test_capitalization()
{
    auto base = std::make_unique<ConcreteComponent>();
    CapitalizeDecorator decorator(std::move(base));

    std::string input = "testuojama aB \ncDe f\tG";
    std::string expected = "Testuojama AB \nCDe F\tG";

    std::string result = decorator.process(input);
    int mistakes = decorator.countMistakes(input);
    assert(result == expected);
    assert(mistakes == 4);
}
void test_punctuation()
{
    auto base = std::make_unique<ConcreteComponent>();
    CommaDecorator decorator(std::move(base));

    std::string input = "Pirmas,vienas, antrasis,  kitas ,anas";
    std::string expected = "Pirmas, vienas, antrasis, kitas, anas";

    std::string result = decorator.process(input);
    int mistakes = decorator.countMistakes(input);
    assert(result == expected);
    assert(mistakes == 3);
}
void test_identation()
{
    auto base = std::make_unique<ConcreteComponent>();
    IndentationDecorator decorator(std::move(base));

    std::string input = "Burbulas \n Ir    \n\tBurbulienė virė \n\nskanią vakarienę,\nBurbulienė\tparagavo";
    std::string expected = "Burbulas \n\t Ir    \n\tBurbulienė virė \n\n\tskanią vakarienę,\n\tBurbulienė\tparagavo";

    std::string result = decorator.process(input);
    int mistakes = decorator.countMistakes(input);
    assert(result == expected);
    assert(mistakes == 3);
}

int main()
{
    FILE *file;
    try
    {
        file = freopen("test_otp.txt", "w", stderr);
    }
    catch (const FileException &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cerr << "testing capitalization: ";
    test_capitalization();
    std::cerr << "\ntesting punctuation: ";
    test_punctuation();
    std::cerr << "\ntesting identation: ";
    test_identation();

    std::cerr << "\nAll tests passed successfully\n";
    fclose(file);
    return 0;
}