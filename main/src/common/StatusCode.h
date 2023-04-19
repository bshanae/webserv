#pragma once

#include <string>

namespace webserv
{
	enum StatusCode
	{
		StatusCodeOk = 200,
		StatusCodeCreated = 201,
		StatusCodeNoContent = 204,
		StatusCodeRedirect = 301,
		StatusCodeBadRequest = 400,
		StatusCodeForbidden = 403,
		StatusCodeNotFound = 404,
		StatusCodeMethodNowAllowed = 405,
		StatusCodePayloadTooLarge = 413,
		StatusCodeInternalServerError = 500,
	};
}

std::string defaultReason(webserv::StatusCode code);