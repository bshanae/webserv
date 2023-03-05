#pragma once

#include <string>
#include <set>

class Config
{
public:

	std::string getProjectRoot() const;

	std::set<std::string> getCGIRoots() const;
	std::set<std::string> getCGIExtensions() const;

	std::string getServerHost() const;
	std::string getServerAddress() const;
	int getServerPort() const;
};
