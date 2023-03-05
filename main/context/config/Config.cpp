#include "Config.h"

std::string Config::getProjectRoot() const
{
	return "main/res/examples/cgi-3";
}

std::set<std::string> Config::getCGIRoots() const
{
	std::set<std::string> result;
	result.insert("/cgi-bin");

	return result;
}

std::set<std::string> Config::getCGIExtensions() const
{
	std::set<std::string> result;
	result.insert(".py");

	return result;
}

std::string Config::getServerHost() const
{
	return "0.0.0.0";
}

std::string Config::getServerAddress() const
{
	return "0.0.0.0";
}

int Config::getServerPort() const
{
	return 80;
}
