#pragma once

#include <iosfwd>

namespace webserv
{
	enum RequestMethod
	{
		RequestMethodGET,
		RequestMethodHEAD,
		RequestMethodPUT,
		RequestMethodPOST,
		RequestMethodDELETE
	};
}

std::istream& operator>>(std::istream& stream, webserv::RequestMethod& method);
std::string toString(webserv::RequestMethod method);