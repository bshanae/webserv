#include "FileException.h"

#include <stdexcept>

FileException::FileException(const std::string& message) : std::runtime_error(message)
{
}