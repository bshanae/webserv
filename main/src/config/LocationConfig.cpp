#include "LocationConfig.h"

#include "utils/algo/str.h"
#include "config/utils.h"

using namespace webserv;
using namespace webserv::config;

std::istream& operator>>(std::istream& source, webserv::config::LocationConfig& config)
{
	std::string line;
	while (utils::getLine(source, line))
	{
		if (utils::isIgnored(line))
		{
		}
		else if (utils::isBlockEnd(line))
		{
			break;
		}
		else if (algo::startsWith(line, "remote"))
		{
			config._remotePath = utils::extractArgument(line);
		}
		else if (algo::startsWith(line, "local"))
		{
			config._localPath = utils::extractArgument(line);
		}
		else if (algo::startsWith(line, "methods"))
		{
			std::vector<RequestMethod> v = utils::extractArguments<RequestMethod>(line);
			config._methods = std::set<RequestMethod>(v.begin(), v.end());
		}
	}

	return source;
}

const std::string& LocationConfig::remotePath() const
{
	return _remotePath;
}

const std::string& LocationConfig::localPath() const
{
	return _localPath;
}

const std::set<RequestMethod>& LocationConfig::methods() const
{
	return _methods;
}