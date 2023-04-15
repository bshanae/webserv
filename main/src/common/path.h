#pragma once

#include <string>

namespace webserv
{
	std::string directoryRemoteView(const std::string& path);
	std::string directoryLocalView(const std::string& path);
}