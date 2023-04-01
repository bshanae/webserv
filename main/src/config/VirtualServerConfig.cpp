#include "VirtualServerConfig.h"

#include "utils/algo/str.h"
#include "config/utils.h"
#include "common/WebAddress.h"

using namespace webserv;
using namespace webserv::config;

std::istream& operator>>(std::istream& source, webserv::config::VirtualServerConfig& config)
{
	std::string line;
	while (utils::getLine(source, line))
	{
		if (utils::isIgnored(line))
		{
			continue;
		}
		else if (utils::isBlockEnd(line))
		{
			break;
		}
		else if (algo::startsWith(line, "name"))
		{
			config._name = utils::extractArgument(line);
		}
		else if (algo::startsWith(line, "address"))
		{
			config._address = utils::extractArgument<WebAddress>(line);
		}
		else if (algo::startsWith(line, "root"))
		{
			config._root = utils::extractArgument(line);
		}
		else if (algo::startsWith(line, "location"))
		{
			LocationConfig location;
			source >> location;

			config._locations.push_back(location);
		}
		else if (algo::startsWith(line, "autoindex"))
		{
			config._autoindex = utils::extractArgument<bool>(line);
		}
		else if (algo::startsWith(line, "cgi"))
		{
			source >> config._cgi;
		}
		else
		{
			throw ParsingException("Invalid line: " + line);
		}
	}

	return source;
}

VirtualServerConfig::VirtualServerConfig() : _autoindex(false)
{}

const std::string& VirtualServerConfig::name() const
{
	return _name;
}

const WebAddress& VirtualServerConfig::address() const
{
	return _address;
}

const std::string& VirtualServerConfig::root() const
{
	return _root;
}

const std::vector<LocationConfig>& VirtualServerConfig::locations() const
{
	return _locations;
}

bool VirtualServerConfig::autoindex() const
{
	return _autoindex;
}

const CGIConfig& VirtualServerConfig::cgi() const
{
	return _cgi;
}