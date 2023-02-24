#include "HeaderType.h"

#include "tools/exceptions/InvalidArgumentException.h"

std::string toString(HeaderType responseHeader)
{
	switch (responseHeader)
	{
		case HeaderTypeDate:
			return "Date";

		case HeaderTypeServer:
			return "Server";

		case HeaderTypeContentLength:
			return "Content-Length";

		case HeaderTypeContentType:
			return "Content-Type";

		default:
			throw InvalidArgumentException();
	}
}