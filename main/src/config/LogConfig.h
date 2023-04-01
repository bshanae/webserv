#pragma once

#include <istream>

namespace webserv
{
	namespace config
	{
		class LogConfig;
	}
}

std::istream& operator>>(std::istream& source, webserv::config::LogConfig& config);

class webserv::config::LogConfig
{
	friend std::istream& ::operator>>(std::istream& source, webserv::config::LogConfig& config);

public:

	static LogConfig makeDefault();

	bool verboseLevelEnabled() const;
	bool infoLevelEnabled() const;
	bool warningLevelEnabled() const;
	bool errorLevelEnabled() const;

private:

	bool _verboseLevelEnabled;
	bool _infoLevelEnabled;
	bool _warningLevelEnabled;
	bool _errorLevelEnabled;
};