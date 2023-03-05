#pragma once

#include <iosfwd>

enum RequestMethod
{
	RequestMethodGET,
	RequestMethodPUT,
	RequestMethodPOST
};

std::istream& operator>>(std::istream& stream, RequestMethod& method);
std::string to_string(RequestMethod method);