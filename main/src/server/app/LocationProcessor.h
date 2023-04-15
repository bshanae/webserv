#pragma once

#include <vector>
#include "config/LocationConfig.h"

namespace webserv
{
	class LocationProcessor;
}

class webserv::LocationProcessor
{
public:

	LocationProcessor(const std::vector<config::LocationConfig>& locations);

	const config::LocationConfig& resolveLocation(const std::string& path) const;

private:

	std::vector<config::LocationConfig> _locations;
};
