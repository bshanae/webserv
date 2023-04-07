#pragma once

#include <string>
#include "utils/templates/Optional.h"
#include "common/WebAddress.h"
#include "LocationConfig.h"
#include "CGIConfig.h"

namespace webserv
{
	namespace config
	{
		class ServerConfig;
	}
}

std::istream& operator>>(std::istream& source, webserv::config::ServerConfig& config);

class webserv::config::ServerConfig
{
	friend std::istream& ::operator>>(std::istream& source, webserv::config::ServerConfig& config);

public:

	ServerConfig();

	const std::string& name() const;
	const WebAddress& address() const;
	const std::string& root() const;
	const std::vector<LocationConfig>& locations() const;
	bool autoindex() const;
	const CGIConfig& cgi() const;

private:

	std::string _name;
	WebAddress _address;
	std::string _root;
	std::vector<LocationConfig> _locations;
	bool _autoindex;
	CGIConfig _cgi;
};
