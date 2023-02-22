#include "Handler.h"

using namespace log;

Handler::Handler() : enabled(false)
{
}

Handler::Handler(const std::string& prefix, const std::string& suffix) :
	enabled(false),
	_prefix(prefix),
	_suffix(suffix)
{
}

Handler::Handler(const Handler &that)
{
	this->enabled = that.enabled;
	this->_prefix = that._prefix;
	this->_suffix = that._suffix;
}

Handler& Handler::operator=(const Handler &that)
{
	this->enabled = that.enabled;
	this->_prefix = that._prefix;
	this->_suffix = that._suffix;

	return *this;
}