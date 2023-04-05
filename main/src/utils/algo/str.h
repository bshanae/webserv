#pragma once

#include <string>

namespace algo
{
	std::string truncate(const std::string& target, size_t length);

	/// L-trims whitespaces
	std::string ltrim(const std::string& str);

	std::string cut(const std::string& str, size_t begin, size_t end);

	bool startsWith(const std::string& main, const std::string& prefix);

	/// Passes whitespaces
	void pass(const std::string& str, size_t& i);

	void pass(const std::string& str, size_t& i, char ignore);

	void toLower(std::string& target);

	void markEmptyLines(std::string& target, const std::string& endl);

	void replaceAll(std::string& target, const std::string& search, const std::string& replace);
}