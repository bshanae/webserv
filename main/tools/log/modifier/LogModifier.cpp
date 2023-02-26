#include "LogModifier.h"

#include <sstream>

using namespace log;

LogModifier LogModifier::red = LogModifier(31);
LogModifier LogModifier::yellow = LogModifier(33);
LogModifier LogModifier::grey = LogModifier(90);
LogModifier LogModifier::italic = LogModifier(3);
LogModifier LogModifier::reset = LogModifier(0);

LogModifier::LogModifier() : _code(-1)
{
}

LogModifier::LogModifier(const LogModifier &that)
{
	_code = that._code;
}

LogModifier& LogModifier::operator=(const LogModifier &that)
{
	_code = that._code;
	return *this;
}

LogModifier::LogModifier(int code) : _code(code)
{
}

std::string log::to_string(const LogModifier& modifier)
{
	std::stringstream buffer;

	buffer << "\033[";
	buffer << modifier._code << 'm';

	return buffer.str();
}

std::string log::to_string(const std::vector<LogModifier>& modifiers)
{
	if (modifiers.empty())
		return "";

	std::stringstream buffer;

	buffer << "\033[";
	for (int i = 0; i < modifiers.size(); i++)
	{
		if (i > 0)
			buffer << ";";
		buffer << modifiers[i]._code;
	}
	buffer << "m";

	return buffer.str();
}