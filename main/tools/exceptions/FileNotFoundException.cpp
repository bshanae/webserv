#include "FileNotFoundException.h"

#include <stdexcept>
#include <string>

FileNotFoundException::FileNotFoundException(const std::string& fileName) :
	std::runtime_error("File " + fileName + " not found!")
{
}