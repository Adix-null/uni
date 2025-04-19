#ifndef DECORATOR_HPP
#define DECORATOR_HPP

#include "Component.hpp"

// Formatter
// Text formatter - implements decorator pattern. Base classes for definitions and managing components, decorators implement the logic and transform text in a specific way(e.g. lowercase, trim). Exception class for any errors.
// To use the project, go to the containing folder in the terminal and run
//```make``` to transform a file
//```make test``` to run the tests
//```make clean``` to remove generated temporary files

class Decorator : public Component
{
protected:
    Component *component;

public:
    Decorator(Component *c) : component(c) {}
    virtual ~Decorator() { delete component; }

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
