#ifndef DECORATOR_HPP
#define DECORATOR_HPP

#include "Component.hpp"

class Decorator : public Component
{
protected:
    Component *component;

public:
    Decorator(Component *c) : component(c) {}
    virtual ~Decorator() { delete component; }
};

#endif
