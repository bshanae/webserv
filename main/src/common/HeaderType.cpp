#include "HeaderType.h"

#include "utils/exceptions/InvalidArgumentException.h"

using namespace webserv;

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