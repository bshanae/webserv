#pragma once

#include <iostream>
#include <vector>
#include "log/logModifier/LogModifier.h"
#include "utils/templates/Optional.h"

namespace webserv
{
	namespace log
	{
		class LogStream;
		typedef void (* LogStreamDelegate)(LogStream& stream);
	}
}

template<typename T>
webserv::log::LogStream& operator<<(webserv::log::LogStream& stream, const T& data);

webserv::log::LogStream& operator<<(webserv::log::LogStream& stream, std::basic_ostream<char>& (* delegate)(std::basic_ostream<char>&));
webserv::log::LogStream& operator<<(webserv::log::LogStream& stream, webserv::log::LogStreamDelegate delegate);

class webserv::log::LogStream
{
	template<typename T>
	friend LogStream& ::operator<<(LogStream& stream, const T& data);

	friend LogStream& ::operator<<(LogStream& stream, std::basic_ostream<char>& (* delegate)(std::basic_ostream<char>&));
	friend LogStream& ::operator<<(LogStream& stream, LogStreamDelegate delegate);

public:

	bool enabled;

	LogStream();
	explicit LogStream(const LogModifier& permanentModifier);

	void addModifier(const LogModifier& modifier);
	void resetModifiers();

private:

	std::string _cachedPrefix;
	std::string _cachedSuffix;
	Optional<LogModifier> _permanentModifier;
	std::vector<LogModifier> _modifiers;

	void updatePrefix();
	void updateSuffix();
};

template<typename T>
webserv::log::LogStream& operator<<(webserv::log::LogStream& stream, const T& data)
{
	if (!stream.enabled)
		return stream;

	std::cout << stream._cachedPrefix;
	std::cout << data;
	std::cout << stream._cachedSuffix;

	return stream;
}