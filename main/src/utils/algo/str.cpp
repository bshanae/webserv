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

std::string algo::range(const std::string& str, size_t begin, size_t end)
{
	return str.substr(begin, end - begin);
}

bool algo::startsWith(const std::string& main, const std::string& prefix)
{
	int i = 0;
	for (; i < prefix.length() && i < main.length(); i++)
	{
		if (main[i] != prefix[i])
			break;
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

void algo::markEndl(std::string& target, const std::string& endl)
{
	replaceAll(target, endl, "$" + endl);
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

static bool matchHelper(const std::string& pattern, const std::string& target, int iPattern, int iTarget)
{
	if (iPattern == pattern.length())
		return iTarget == target.length();

	if (pattern[iPattern] == '*')
	{
		if (iTarget == target.length())
			return matchHelper(pattern, target, iPattern + 1, iTarget);

		return matchHelper(pattern, target, iPattern, iTarget + 1) ||
			   matchHelper(pattern, target, iPattern + 1, iTarget);
	}
	else
	{
		if (iTarget == target.length())
			return iPattern == pattern.length();

		return pattern[iPattern] == target[iTarget] &&
		       matchHelper(pattern, target, iPattern + 1, iTarget + 1);
	}
}

bool algo::match(const std::string& pattern, const std::string& target)
{
	return matchHelper(pattern, target, 0, 0);
}