#include "LocationProcessor.h"

#include "utils/algo/str.h"
#include "common/exceptions/WebException.h"

using namespace webserv;

LocationProcessor::LocationProcessor(const std::vector<Location>& locations) : _locations(locations)
{

}

const Location& LocationProcessor::resolveLocation(const std::string& path) const
{
	const Location* bestMatch = nullptr;
	size_t bestMatchLength = 0;

	for (std::vector<Location>::const_iterator l = _locations.begin(); l != _locations.end(); l++)
	{
		if (!algo::startsWith(path, l->remotePath()))
			continue;

		const size_t matchLength = l->remotePath().length();
		if (l->remotePath().length() > bestMatchLength)
		{
			bestMatch = &*l;
			bestMatchLength = matchLength;
		}
	}

	if (bestMatch == nullptr)
		throw WebException(StatusCodeNotFound, "Can't resolve location '" + path + "'");

	return *bestMatch;
}
