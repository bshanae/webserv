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

std::istream& operator>>(std::istream& source, webserv::config::CGIConfig& config);

class webserv::config::CGIConfig
{
	friend std::istream& ::operator>>(std::istream& source, webserv::config::CGIConfig& config);

public:

	const std::set<std::string>& roots() const;
	const std::set<std::string>& extensions() const;

private:

	std::set<std::string> _roots;
	std::set<std::string> _extensions;
};
