#include "str.h"

void markEmptyLines(std::string& target, const std::string& endl)
{
	replaceAll(target, endl + endl, endl + "$" + endl);

	const size_t lastEndlOffset = target.length() - endl.length();
	if (target.compare(lastEndlOffset, endl.length(), endl) == 0)
		target.replace(lastEndlOffset, endl.length(), endl + "$");
}

void replaceAll(std::string& target, const std::string& search, const std::string& replace)
{
	size_t i = 0;
	while ((i = target.find(search, i)) != std::string::npos)
	{
		target.replace(i, search.length(), replace);
		i += replace.length();
	}
}