#pragma once

#include <string>

namespace sys
{
	namespace path
	{
		std::string extension(const std::string& path);
		std::string directory(const std::string& path);
		std::string concat(const std::string& a, const std::string& b);
		std::string removeTrailingSplash(const std::string& path);
	}
};