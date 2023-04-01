#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "utils/algo/str.h"
#include "utils/exceptions/ParsingException.h"

namespace webserv
{
	namespace config
	{
		namespace utils
		{
			bool isIgnored(const std::string& line);
			bool isBlockEnd(const std::string& line);

			bool getLine(std::istream& stream, std::string& line);
			std::vector<std::string> breakLine(const std::string& line);

			std::string extractArgument(const std::string& line);
			std::vector<std::string> extractArguments(const std::string& line);

			template <typename T>
			T extractArgument(const std::string& line)
			{
				std::string argStr = extractArgument(line);

				std::stringstream argStream = std::stringstream(argStr);

				T value;
				argStream >> value;

				return value;
			}

			template<typename T>
			std::vector<T> extractArguments(const std::string& line)
			{
				const std::vector<std::string> argStrs = extractArguments(line);

				std::vector<T> values;
				for (int i = 0; i < argStrs.size(); i++)
				{
					std::stringstream argStream = std::stringstream(argStrs[i]);

					T value;
					argStream >> value;

					values.push_back(value);
				}
				
				return values;
			}
		}
	}
}