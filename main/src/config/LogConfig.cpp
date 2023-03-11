#include "LogConfig.h"

using namespace webserv::config;

bool LogConfig::verboseLevelEnabled() const
{
	return true;
}

bool LogConfig::infoLevelEnabled() const
{
	return true;
}

bool LogConfig::warningLevelEnabled() const
{
	return true;
}

bool LogConfig::errorLevelEnabled() const
{
	return true;
}