#pragma once

#include <vector>
#include "LogConfig.h"
#include "MediaConfig.h"
#include "VirtualServerConfig.h"

class Config
{
public:

	Config();

	LogConfig log() const;
	MediaConfig media() const;
	const std::vector<VirtualServerConfig>& virtualServers() const;

private:

	std::vector<VirtualServerConfig> _virtualServers;
};
