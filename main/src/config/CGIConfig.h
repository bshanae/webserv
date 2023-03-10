#pragma once

#include <string>
#include <set>

class CGIConfig
{
public:

	std::set<std::string> roots() const;
	std::set<std::string> extensions() const;
};
