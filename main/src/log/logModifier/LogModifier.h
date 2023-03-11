#pragma once

#include <string>
#include <vector>

namespace webserv
{
	namespace log
	{
		class LogModifier;
	}
}

std::string toString(const webserv::log::LogModifier& modifier);
std::string toString(const std::vector<webserv::log::LogModifier>& modifiers);

class webserv::log::LogModifier
{
	friend std::string (::toString)(const LogModifier& modifier);
	friend std::string (::toString)(const std::vector<LogModifier>& modifiers);

public:

	static LogModifier red;
	static LogModifier yellow;
	static LogModifier grey;
	static LogModifier italic;
	static LogModifier reset;

	LogModifier();

private:

	int _code;

	explicit LogModifier(int code);
};