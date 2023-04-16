#include "ServerConfig.h"

#include "utils/algo/str.h"
#include "common/WebAddress.h"
#include "common/path.h"
#include "config/utils.h"

using namespace webserv;
using namespace webserv::config;

std::istream& operator>>(std::istream& source, webserv::config::ServerConfig& config)
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
			config._root = directoryLocalView(utils::extractArgument(line));
		}
		else if (algo::startsWith(line, "location"))
		{
			LocationConfig location;
			source >> location;

			config._locations.push_back(location);
		}
		else if (algo::startsWith(line, "max_client_body_size"))
		{
			config._maxClientBodySize = utils::extractArgument<size_t>(line);
		}
		else
		{
			throw ParsingException("Invalid line: " + line);
		}
	}

	return source;
}

ServerConfig::ServerConfig()
{}

const std::string& ServerConfig::name() const
{
	return _name;
}

const WebAddress& ServerConfig::address() const
{
	return _address;
}

const std::string& ServerConfig::root() const
{
	return _root;
}

const std::vector<LocationConfig>& ServerConfig::locations() const
{
	return _locations;
}

const Optional<size_t>& ServerConfig::maxClientBodySize() const
{
	return _maxClientBodySize;
}