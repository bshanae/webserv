#include "sys.path.h"

std::string sys::path::extension(const std::string& path)
{
	const size_t dotIndex = path.find_last_of('.');
	if (dotIndex == std::string::npos)
		return "";

	return path.substr(dotIndex, path.size() - dotIndex);
}

std::string sys::path::directory(const std::string& path)
{
	const size_t lastSlashIndex = path.rfind('/');
	if (std::string::npos == lastSlashIndex)
		return "";

	return path.substr(0, lastSlashIndex);
}

std::string sys::path::concat(const std::string& a, const std::string& b)
{
	if (a.empty())
		return b;
	if (b.empty())
		return a;

	if (a == "." && b[0] == '.')
		return b;

	if (a[a.length() - 1] == '/' || b[0] == '/')
		return a + b;
	else
		return a + '/' + b;
}