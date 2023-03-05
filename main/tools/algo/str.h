#pragma once

#include <string>

namespace algo
{
	std::string truncate(const std::string& target, size_t length);

	void toLower(std::string& target);
	void markEmptyLines(std::string& target, const std::string& endl);
	void replaceAll(std::string& target, const std::string& search, const std::string& replace);
}