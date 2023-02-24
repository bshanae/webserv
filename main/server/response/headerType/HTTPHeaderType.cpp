#include "HTTPHeaderType.h"

#include "tools/exceptions/InvalidArgumentException.h"

std::string toString(HTTPHeaderType responseHeader)
{
	switch (responseHeader)
	{
		case HTTPHeaderTypeDate:
			return "Date";

		case HTTPHeaderTypeServer:
			return "Server";

		case HTTPHeaderTypeContentLength:
			return "Content-Length";

		case HTTPHeaderTypeContentType:
			return "Content-Type";

		default:
			throw InvalidArgumentException();
	}
}