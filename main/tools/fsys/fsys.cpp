#include "fsys.h"

std::string fsys::extension(const std::string& path)
{
	const size_t dotIndex = path.find_last_of('.');
	if (dotIndex == std::string::npos)
		return "";

	return path.substr(dotIndex, path.size() - dotIndex);
}

std::string fsys::concatPath(const std::string& a, const std::string& b)
{
	if (a.empty())
		return b;
	if (b.empty())
		return a;

	if (a[a.length() - 1] == '/' || b[0] == '/')
		return a + b;
	else
		return a + '/' + b;
}