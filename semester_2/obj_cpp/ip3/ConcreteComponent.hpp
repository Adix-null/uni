#ifndef CONCRETE_COMPONENT_HPP
#define CONCRETE_COMPONENT_HPP

#include "Component.hpp"

class ConcreteComponent : public Component
{
public:
    std::string process(const std::string &text) override
    {
        return text;
    }
};

#endif
