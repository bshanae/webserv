#pragma once

#include <string>

enum HeaderType
{
	HeaderTypeDate,
	HeaderTypeServer,
	HeaderTypeContentLength,
	HeaderTypeContentType,
};


std::string toString(HeaderType responseHeader);