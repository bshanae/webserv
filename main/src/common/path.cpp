#include "path.h"

std::string webserv::directoryRemoteView(const std::string& path)
{
	if (path.length() == 0)
		return path;
	if (path[path.length() - 1] != '/')
		return path;

	return path.substr(0, path.length() - 1);
}

std::string webserv::directoryLocalView(const std::string& path)
{
	if (path.length() >= 1 && path[0] == '/')
		return "./" + path.substr(1, path.length() - 1);
	if (path.length() >= 2 && path[0] == '.' && path[0] == '/')
		return "./" + path.substr(2, path.length() - 2);

	return path;
}