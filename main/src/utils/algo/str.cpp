#include "str.h"

std::string algo::truncate(const std::string& target, const size_t length)
{
	if (target.length() > length)
		return target.substr(0, length) + "...";

	return target;
}

std::string algo::ltrim(const std::string& str)
{
	size_t i = 0;
	pass(str, i);

	return str.substr(i, str.length());
}

bool algo::startsWith(const std::string& main, const std::string& prefix)
{
	int i = 0;
	for (; i < prefix.length() && i < main.length(); i++)
	{
		if (main[i] != prefix[i])
			return false;
	}

	return i == prefix.length();
}

void algo::pass(const std::string& str, size_t& i)
{
	while (std::isspace(str[i]))
		i++;
}

void algo::pass(const std::string& str, size_t& i, char ignore)
{
	while (str[i] == ignore)
		i++;
}

void algo::toLower(std::string& target)
{
	for (int i = 0; i < target.length(); i++)
		target[i] = std::tolower(target[i]);
}

void algo::markEmptyLines(std::string& target, const std::string& endl)
{
	replaceAll(target, endl + endl, endl + "$" + endl);

	const size_t lastEndlOffset = target.length() - endl.length();
	if (target.compare(lastEndlOffset, endl.length(), endl) == 0)
		target.replace(lastEndlOffset, endl.length(), endl + "$");
}

void algo::replaceAll(std::string& target, const std::string& search, const std::string& replace)
{
	size_t i = 0;
	while ((i = target.find(search, i)) != std::string::npos)
	{
		target.replace(i, search.length(), replace);
		i += replace.length();
	}
}