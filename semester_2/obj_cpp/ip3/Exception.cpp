#include "Exception.hpp"

ProcessException::ProcessException(const std::string &message) : msg(message) {}

const char *ProcessException::what() const noexcept
{
    return msg.c_str();
}

FileException::FileException() : ProcessException("Error: Cannot open file\n") {}