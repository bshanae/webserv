#pragma once

#include <string>
#include <vector>

namespace log
{
	class LogModifier
	{
	public:

		static LogModifier red;
		static LogModifier yellow;
		static LogModifier grey;
		static LogModifier italic;
		static LogModifier reset;

		LogModifier();

		friend std::string to_string(const LogModifier& modifier);
		friend std::string to_string(const std::vector<LogModifier>& modifiers);

	private:

		int _code;

		explicit LogModifier(int code);
	};

	std::string to_string(const LogModifier& modifier);
	std::string to_string(const std::vector<LogModifier>& modifiers);
}