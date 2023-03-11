#pragma once

#include <string>

namespace webserv
{
	enum StatusCode
	{
		StatusCodeOk = 200,
		StatusCodeBadRequest = 400,
		StatusCodeNotFound = 404,
		StatusCodeInternalServerError = 500,
	};
}

std::string defaultReason(webserv::StatusCode code);