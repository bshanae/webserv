#include "MediaType.h"

#include "tools/exceptions/InvalidArgumentException.h"

std::string toString(MediaType mediaType)
{
	switch (mediaType)
	{
		case MediaTypeHtml:
			return "text/html";

		default:
			throw InvalidArgumentException();
	}
}