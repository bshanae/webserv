#include "HTTPStatusCode.h"

#include "tools/exceptions/InvalidArgumentException.h"

std::string defaultReason(HTTPStatusCode code)
{
	switch (code)
	{
		case HTTPStatusCodeOk:
			return "OK";

		case HTTPStatusCodeNotFound:
			return "Not found";

		default:
			throw InvalidArgumentException();
	}
}