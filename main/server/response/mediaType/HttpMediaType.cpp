#include "HttpMediaType.h"

#include "tools/exceptions/InvalidArgumentException.h"

std::string toString(HttpMediaType mediaType)
{
	switch (mediaType)
	{
		case HttpMediaTypeHtml:
			return "text/html";

		default:
			throw InvalidArgumentException();
	}
}