#include "LocationProcessor.h"

#include "utils/algo/str.h"
#include "common/exceptions/WebException.h"

using namespace webserv;
using namespace webserv::config;

LocationProcessor::LocationProcessor(const std::vector<LocationConfig>& locations) : _locations(locations)
{

}

const LocationConfig& LocationProcessor::resolveLocation(const std::string& path) const
{
	const LocationConfig* bestMatch = nullptr;
	size_t bestMatchLength = 0;

	for (std::vector<LocationConfig>::const_iterator l = _locations.begin(); l != _locations.end(); l++)
	{
		if (!algo::startsWith(path, l->remotePath()))
			continue;

		const size_t matchLength = l->remotePath().length();
		if (bestMatch == nullptr || l->remotePath().length() > bestMatchLength)
		{
			bestMatch = &*l;
			bestMatchLength = matchLength;
		}
	}

	if (bestMatch == nullptr)
		throw WebException(StatusCodeNotFound, "Can't resolve location '" + path + "'");

	return *bestMatch;
}
