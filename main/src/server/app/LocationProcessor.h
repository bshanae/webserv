#pragma once

#include "common/Location.h"

namespace webserv
{
	class LocationProcessor;
}

class webserv::LocationProcessor
{
public:

	LocationProcessor(const std::vector<Location>& locations);

	const Location& resolveLocation(const std::string& path) const;

private:

	std::vector<Location> _locations;
};
