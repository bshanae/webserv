#pragma once

#include <string>

enum StatusCode
{
	StatusCodeOk = 200,
	StatusCodeNotFound = 404
};

std::string defaultReason(StatusCode code);