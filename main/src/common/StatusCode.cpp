#include "StatusCode.h"

#include "utils/exceptions/InvalidArgumentException.h"

using namespace webserv;

std::string defaultReason(StatusCode code)
{
	switch (code)
	{
		case StatusCodeOk:
			return "OK";

		case StatusCodeBadRequest:
			return "Bad request";

		case StatusCodeNotFound:
			return "Not found";

		case StatusCodeMethodNowAllowed:
			return "Method not allowed";

		case StatusCodePayloadTooLarge:
			return "Payload too large";

		case StatusCodeInternalServerError:
			return "Internal server error";

		default:
			throw InvalidArgumentException();
	}
}