#include "SocketException.h"
#include <stdexcept>

SocketException::SocketException(const std::string& message) : std::runtime_error(message)
{
}

SocketException::SocketException() : std::runtime_error("")
{
}