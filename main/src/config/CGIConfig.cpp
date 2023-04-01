#include "CGIConfig.h"

#include "utils/algo/str.h"
#include "config/utils.h"

using namespace webserv::config;

std::istream& operator>>(std::istream& source, webserv::config::CGIConfig& config)
{
	std::string line;
	while (utils::getLine(source, line))
	{
		if (utils::isIgnored(line))
			;
		else if (utils::isBlockEnd(line))
			break;
		else if (algo::startsWith(line, "root"))
			config._roots.insert(utils::extractArgument(line));
		else if (algo::startsWith(line, "extension"))
			config._extensions.insert(utils::extractArgument(line));
		else
			throw ParsingException("Invalid line: " + line);
	}

	return source;
}

const std::set<std::string>& CGIConfig::roots() const
{
	return _roots;
}

const std::set<std::string>& CGIConfig::extensions() const
{
	return _extensions;
}