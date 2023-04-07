#pragma once

#include <vector>
#include "utils/templates/Optional.h"
#include "LogConfig.h"
#include "MediaConfig.h"
#include "ServerConfig.h"

namespace webserv
{
	namespace config
	{
		class Config;
	}
}

std::istream& operator>>(std::istream& source, webserv::config::Config& config);

class webserv::config::Config
{
	friend std::istream& ::operator>>(std::istream& source, Config& config);

public:

	const LogConfig& log() const;
	const MediaConfig& media() const;
	const std::vector<ServerConfig>& servers() const;

private:

	LogConfig _log;
	MediaConfig _media;
	std::vector<ServerConfig> _servers;
};