#pragma once

#include <string>

namespace webserv
{
	enum HeaderType
	{
		HeaderTypeDate,
		HeaderTypeServer,
		HeaderTypeContentLength,
		HeaderTypeContentType,
	};
}

std::string toString(webserv::HeaderType responseHeader);