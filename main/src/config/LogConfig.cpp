#include "LogConfig.h"

#include <istream>
#include "utils/algo/str.h"
#include "utils.h"

using namespace webserv::config;

std::istream& operator>>(std::istream& source, webserv::config::LogConfig& config)
{
	std::string line;
	while (utils::getLine(source, line))
	{
		if (utils::isIgnored(line))
			;
		else if (utils::isBlockEnd(line))
			break;
		else if (algo::startsWith(line, "verbose"))
			config._verboseLevelEnabled = utils::extractArgument<bool>(line);
		else if (algo::startsWith(line, "info"))
			config._infoLevelEnabled = utils::extractArgument<bool>(line);
		else if (algo::startsWith(line, "warning"))
			config._warningLevelEnabled = utils::extractArgument<bool>(line);
		else if (algo::startsWith(line, "error"))
			config._errorLevelEnabled = utils::extractArgument<bool>(line);
	}

	return source;
}

LogConfig LogConfig::makeDefault()
{
	LogConfig config;

	config._verboseLevelEnabled = false;
	config._infoLevelEnabled = false;
	config._warningLevelEnabled = true;
	config._errorLevelEnabled = true;

	return config;
}

bool LogConfig::verboseLevelEnabled() const
{
	return _verboseLevelEnabled;
}

bool LogConfig::infoLevelEnabled() const
{
	return _infoLevelEnabled;
}

bool LogConfig::warningLevelEnabled() const
{
	return _warningLevelEnabled;
}

bool LogConfig::errorLevelEnabled() const
{
	return _errorLevelEnabled;
}