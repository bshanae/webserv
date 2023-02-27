#include "Config.h"

std::string Config::getProjectRoot() const
{
	return "main/res/examples/apps/basic";
}

std::string Config::getServerAddress() const
{
	return "0.0.0.0";
}

int Config::getServerPort() const
{
	return 80;
}
