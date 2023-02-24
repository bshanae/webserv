#pragma once

#include <string>

enum HTTPHeaderType
{
	HTTPHeaderTypeDate,
	HTTPHeaderTypeServer,
	HTTPHeaderTypeContentLength,
	HTTPHeaderTypeContentType,
};


std::string toString(HTTPHeaderType responseHeader);