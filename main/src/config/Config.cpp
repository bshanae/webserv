#include "Config.h"

using namespace webserv::config;

Config::Config()
{
	_virtualServers.push_back(VirtualServerConfig());
}

LogConfig Config::log() const
{
	return LogConfig();
}

MediaConfig Config::media() const
{
	return MediaConfig();
}

const std::vector<VirtualServerConfig>& Config::virtualServers() const
{
	return _virtualServers;
}