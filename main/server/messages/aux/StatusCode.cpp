#include "StatusCode.h"

#include "tools/exceptions/InvalidArgumentException.h"

std::string defaultReason(StatusCode code)
{
	switch (code)
	{
		case StatusCodeOk:
			return "OK";

		case StatusCodeNotFound:
			return "Not found";

		default:
			throw InvalidArgumentException();
	}
}