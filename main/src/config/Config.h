#pragma once

#include <vector>
#include "LogConfig.h"
#include "VirtualServerConfig.h"

class Config
{
public:

	Config();

	LogConfig log() const;
	const std::vector<VirtualServerConfig>& virtualServers() const;

private:

	std::vector<VirtualServerConfig> _virtualServers;
};
