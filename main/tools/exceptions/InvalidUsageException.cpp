#include "InvalidUsageException.h"

#include <stdexcept>

InvalidUsageException::InvalidUsageException(const std::string& message) : std::runtime_error(message)
{
}

InvalidUsageException::InvalidUsageException() : std::runtime_error("Invalid usage!")
{
}