#include "FileException.hpp"
#include <stdexcept>

FileException::FileException(const std::string& message) : std::runtime_error(message)
{
}

FileException::FileException() : std::runtime_error("")
{
}