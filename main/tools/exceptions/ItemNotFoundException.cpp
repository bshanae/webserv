#include "ItemNotFoundException.h"

#include <stdexcept>

ItemNotFoundException::ItemNotFoundException(const std::string& message) : std::runtime_error(message)
{
}

ItemNotFoundException::ItemNotFoundException() : std::runtime_error("Value not found!")
{
}