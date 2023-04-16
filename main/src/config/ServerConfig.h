#pragma once

#include <string>
#include <vector>
#include "utils/templates/Optional.h"
#include "common/WebAddress.h"
#include "LocationConfig.h"

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
	const Optional<size_t>& maxClientBodySize() const;

private:

	std::string _name;
	WebAddress _address;
	std::string _root;
	std::vector<LocationConfig> _locations;
	Optional<size_t> _maxClientBodySize;
};
