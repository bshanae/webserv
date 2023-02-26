#pragma once

#include <iostream>
#include <vector>
#include "tools/log/modifier/LogModifier.h"
#include "tools/templates/Optional.h"

namespace log
{
	class LogStream;
	typedef void (* LogStreamDelegate)(LogStream& stream);

	class LogStream
	{
	public:

		bool enabled;

		LogStream();
		explicit LogStream(const LogModifier& permanentModifier);
		LogStream(const LogStream& that);
		LogStream& operator=(const LogStream& that);

		void addModifier(const LogModifier& modifier);
		void resetModifiers();

		template<typename T>
		friend LogStream& operator<<(LogStream& stream, const T& data);

		friend LogStream& operator<<(LogStream& stream, std::basic_ostream<char>& (* delegate)(std::basic_ostream<char>&));
		friend LogStream& operator<<(LogStream& stream, LogStreamDelegate delegate);

	private:

		std::string _cachedPrefix;
		std::string _cachedSuffix;
		Optional<LogModifier> _permanentModifier;
		std::vector<LogModifier> _modifiers;

		void updatePrefix();
		void updateSuffix();
	};

	template<typename T>
	LogStream& operator<<(LogStream& stream, const T& data)
	{
		if (!stream.enabled)
			return stream;

		std::cout << stream._cachedPrefix;
		std::cout << data;
		std::cout << stream._cachedSuffix;

		return stream;
	}

	log::LogStream& operator<<(log::LogStream& stream, std::basic_ostream<char>& (* delegate)(std::basic_ostream<char>&));
	LogStream& operator<<(LogStream& stream, LogStreamDelegate delegate);
}