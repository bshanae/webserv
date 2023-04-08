#pragma once

#include <string>

namespace webserv
{
	class HeaderName;
}

class webserv::HeaderName : public std::string
{
public:

	static HeaderName Date;
	static HeaderName Server;
	static HeaderName Location;
	static HeaderName ContentLength;
	static HeaderName ContentType;

	HeaderName();
	explicit HeaderName(const std::string& string);
	HeaderName(const char* string);
};