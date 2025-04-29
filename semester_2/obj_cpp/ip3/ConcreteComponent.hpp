#ifndef CONCRETE_COMPONENT_HPP
#define CONCRETE_COMPONENT_HPP

#include "Component.hpp"
#include <string>

class ConcreteComponent : public Component
{
public:
    std::string process(const std::string &text) override;
    int countMistakes(const std::string &text) override;
};

#endif
