#pragma once

#include <string>

namespace str
{
	std::string truncate(const std::string& target, size_t length);
	void markEmptyLines(std::string& target, const std::string& endl);
	void replaceAll(std::string& target, const std::string& search, const std::string& replace);
}