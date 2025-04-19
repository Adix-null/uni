#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>

class Component
{
public:
    virtual ~Component() {}
    virtual std::string process(const std::string &text) = 0;
};

#endif