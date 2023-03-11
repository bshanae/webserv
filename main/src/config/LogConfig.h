#pragma once

namespace webserv
{
	namespace config
	{
		class LogConfig;
	}
}

class webserv::config::LogConfig
{
public:

	bool verboseLevelEnabled() const;
	bool infoLevelEnabled() const;
	bool warningLevelEnabled() const;
	bool errorLevelEnabled() const;
};
