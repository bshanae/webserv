#include "Config.h"

Config::Config()
{
	_virtualServers.push_back(VirtualServerConfig());
}

LogConfig Config::log() const
{
	return LogConfig();
}

const std::vector<VirtualServerConfig>& Config::virtualServers() const
{
	return _virtualServers;
}