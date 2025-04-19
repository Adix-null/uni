#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>

#include "ConcreteComponent.hpp"
#include "CapitalizeDecorator.hpp"

#include "PunctuationDecorator.hpp"
#include "Exception.hpp"

void test_capitalization()
{
    ConcreteComponent *base = new ConcreteComponent();
    CapitalizeDecorator decorator(base);

    std::string input = "\n\t  Testuojama";
    std::string expected = "\n\t  TESTUOJAMA";

    std::string result = decorator.process(input);
    assert(result == expected);
}
void test_punctuation()
{
    ConcreteComponent *base = new ConcreteComponent();
    PunctuationDecorator decorator(base);

    std::string input = "Pirmas,vienas, antrasis,  kitas ,anas";
    std::string expected = "Pirmas, vienas, antrasis, kitas, anas";

    std::string result = decorator.process(input);
    assert(result == expected);
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

    std::cerr << "\ntesting capitalization: ";
    test_capitalization();
    std::cerr << "\ntesting punctuation: ";
    test_punctuation();

    std::cerr << "\nAll tests passed successfully\n";
    fclose(file);
    return 0;
}