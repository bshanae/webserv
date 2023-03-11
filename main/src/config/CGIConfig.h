#pragma once

#include <string>
#include <set>

namespace webserv
{
	namespace config
	{
		class CGIConfig;
	}
}

class webserv::config::CGIConfig
{
public:

	std::set<std::string> roots() const;
	std::set<std::string> extensions() const;
};
