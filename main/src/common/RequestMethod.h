#pragma once

#include <iosfwd>

namespace webserv
{
	enum RequestMethod
	{
		RequestMethodGET,
		RequestMethodPUT,
		RequestMethodPOST
	};
}

std::istream& operator>>(std::istream& stream, webserv::RequestMethod& method);
std::string toString(webserv::RequestMethod method);