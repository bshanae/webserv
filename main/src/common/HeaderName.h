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
	static HeaderName Host;
	static HeaderName Location;
	static HeaderName ContentLength;
	static HeaderName ContentType;
	static HeaderName TransferEncoding;
	static HeaderName Cookie;

	HeaderName();
	explicit HeaderName(const std::string& string);
	HeaderName(const char* string);
};