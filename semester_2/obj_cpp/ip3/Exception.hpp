#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cassert>
#include <memory>

class ProcessException : public std::exception
{
public:
    explicit ProcessException(const std::string &message);
    const char *what() const noexcept override;

private:
    std::string msg;
};

class FileException : public ProcessException
{
public:
    FileException();
};

#endif