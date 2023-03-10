#include "io.h"

#include <sstream>

std::string io::to_string(std::ostream& stream)
{
	std::stringstream buffer;
	buffer << stream.rdbuf();

	return buffer.str();
}