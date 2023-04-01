#include "Config.h"

#include "utils/algo/str.h"
#include "config/utils.h"

using namespace webserv::config;

std::istream& operator>>(std::istream& source, webserv::config::Config& config)
{
	Optional<LogConfig> log;
	Optional<MediaConfig> media;

	std::string line;
	while (utils::getLine(source, line))
	{
		if (utils::isIgnored(line))
		{
		}
		else if (algo::startsWith(line, "log"))
		{
			if (utils::extractArgument<std::string>(line) == "default")
			{
				log = LogConfig::makeDefault();
			}
			else
			{
				log = LogConfig();
				source >> *log;
			}
		}
		else if (algo::startsWith(line, "media"))
		{
			if (utils::extractArgument<std::string>(line) == "default")
			{
				media = MediaConfig::makeDefault();
			}
			else
			{
				media = MediaConfig();
				source >> *media;
			}
		}
		else if (algo::startsWith(line, "server"))
		{
			config._virtualServers.push_back(VirtualServerConfig());
			source >> config._virtualServers.back();
		}
		else
		{
			throw ParsingException("Invalid line: " + line);
		}
	}

	if (!log)
		throw ParsingException("Logging is not configured");
	config._log = *log;

	if (!media)
		throw ParsingException("Media types are not configured");
	config._media = *media;

	return source;
}

const LogConfig& Config::log() const
{
	return _log;
}

const MediaConfig& Config::media() const
{
	return _media;
}

const std::vector<VirtualServerConfig>& Config::virtualServers() const
{
	return _virtualServers;
}