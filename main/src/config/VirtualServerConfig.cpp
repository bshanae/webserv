#include "VirtualServerConfig.h"

using namespace webserv;
using namespace webserv::config;

std::string VirtualServerConfig::root() const
{
	return "main/res/examples/cgi-3";
}

WebAddress VirtualServerConfig::address() const
{
	return WebAddress("0.0.0.0", 80);
}

bool VirtualServerConfig::autoindex() const
{
	return false;
}

CGIConfig VirtualServerConfig::cgi() const
{
	return CGIConfig();
}