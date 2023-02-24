#include "InvalidStateException.h"

#include <stdexcept>

InvalidStateException::InvalidStateException(const std::string& message) : std::runtime_error(message)
{
}

InvalidStateException::InvalidStateException() : std::runtime_error("Invalid state!")
{
}