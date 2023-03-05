#include "ParsingException.h"

ParsingException::ParsingException(const std::string& message) : std::runtime_error(message)
{
}