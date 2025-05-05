#ifndef DECORATOR_HPP
#define DECORATOR_HPP

#include "Component.hpp"
#include <memory>

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
