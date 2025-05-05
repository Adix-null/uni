#ifndef DECORATOR_HPP
#define DECORATOR_HPP

#include "Component.hpp"
#include <memory>

// Formatter
// Text formatter - implements decorator pattern. Base classes for definitions and managing components, decorators implement the logic and transform text in a specific way(e.g. lowercase, trim). Exception class for any errors.
// Component defines the structure of the text processor, the Decorator class is a base class for all decorators and ConcreteComponent is the main class that various decorators attach to.
// To use the project, go to the containing folder in the terminal and run
//```make``` to transform a file
//```make test``` to run the tests
//```make clean``` to remove generated temporary files

class Decorator : public Component
{
protected:
    std::unique_ptr<Component> component;

public:
    explicit Decorator(std::unique_ptr<Component> c) : component(std::move(c)) {}
    virtual ~Decorator() = default;

    virtual std::string process(const std::string &text) override
    {
        return component->process(text);
    }

    virtual int countMistakes(const std::string &text) override
    {
        return component->countMistakes(text);
    }
};

#endif
