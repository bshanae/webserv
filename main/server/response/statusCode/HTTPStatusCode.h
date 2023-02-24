#pragma once

#include <string>

enum HTTPStatusCode
{
	HTTPStatusCodeOk = 200,
	HTTPStatusCodeNotFound = 404
};

std::string defaultReason(HTTPStatusCode code);