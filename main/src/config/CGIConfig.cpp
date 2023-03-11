#include "CGIConfig.h"

using namespace webserv::config;

std::set<std::string> CGIConfig::roots() const
{
	std::set<std::string> result;
	result.insert("/cgi-bin");

	return result;
}

std::set<std::string> CGIConfig::extensions() const
{
	std::set<std::string> result;
	result.insert(".py");

	return result;
}