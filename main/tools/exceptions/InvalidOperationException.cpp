#include "InvalidOperationException.h"

#include <stdexcept>

InvalidOperationException::InvalidOperationException(const std::string& message) : std::runtime_error(message)
{
}

InvalidOperationException::InvalidOperationException() : std::runtime_error("Invalid operation!")
{
}