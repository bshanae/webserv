#include "SystemException.h"

SystemException::SystemException(const std::string& message) : std::runtime_error(message)
{
}