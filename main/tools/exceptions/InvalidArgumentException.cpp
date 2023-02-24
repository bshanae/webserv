#include "InvalidArgumentException.h"

#include <stdexcept>
#include <string>

InvalidArgumentException::InvalidArgumentException(const std::string& argumentName) :
	std::runtime_error("Invalid argument: " + argumentName)
{
}

InvalidArgumentException::InvalidArgumentException() : std::runtime_error("Invalid argument!")
{
}