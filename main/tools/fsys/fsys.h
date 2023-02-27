#pragma once

#include <string>

namespace fsys
{
	std::string extension(const std::string& path);
	std::string concatPath(const std::string& a, const std::string& b);
};
