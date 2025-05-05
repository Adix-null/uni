#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>

class Component
{
public:
    virtual ~Component() = default;
    virtual std::string process(const std::string &text) = 0;
    virtual int countMistakes(const std::string &text) = 0;
};

#endif