#pragma once

#include <string>

namespace log
{
	namespace AnsiCodes
	{
		std::string Red = "\033[31m";
		std::string Yellow = "\033[33m";

		std::string Bold = "\033[1m";
		std::string Italic = "\033[3m";

		std::string Reset = "\033[0m";
	}
}