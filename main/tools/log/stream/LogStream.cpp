#include "LogStream.h"

using namespace log;

LogStream::LogStream() : enabled(false)
{
	updatePrefix();
	updateSuffix();
}

LogStream::LogStream(const LogModifier& permanentModifier) :
	enabled(false),
	_permanentModifier(permanentModifier)
{
	_modifiers.push_back(permanentModifier);

	updatePrefix();
	updateSuffix();
}

void LogStream::addModifier(const LogModifier &modifier)
{
	_modifiers.push_back(modifier);
	updatePrefix();
}

void LogStream::resetModifiers()
{
	_modifiers.clear();
	if (_permanentModifier)
		_modifiers.push_back(*_permanentModifier);

	updatePrefix();
}

void LogStream::updatePrefix()
{
	this->_cachedPrefix = to_string(_modifiers);
}

void LogStream::updateSuffix()
{
	this->_cachedSuffix = to_string(LogModifier::reset);
}

log::LogStream& log::operator<<(log::LogStream& stream, std::basic_ostream<char>& (*delegate)(std::basic_ostream<char>&))
{
	if (!stream.enabled)
		return stream;

	std::cout << stream._cachedPrefix;
	delegate(std::cout);
	std::cout << stream._cachedSuffix;

	return stream;
}

LogStream& log::operator<<(LogStream& stream, LogStreamDelegate delegate)
{
	if (!stream.enabled)
		return stream;

	std::cout << stream._cachedPrefix;
	delegate(stream);
	std::cout << stream._cachedSuffix;

	return stream;
}