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
		const size_t matchLength = match(l->remotePath(), path);

		// check match
		if (matchLength == 0 && !l->remotePath().empty())
			continue;

		// try update best match
		if (bestMatch == nullptr || matchLength > bestMatchLength)
		{
			bestMatch = &*l;
			bestMatchLength = matchLength;
		}
	}

	if (bestMatch == nullptr)
		throw WebException(StatusCodeNotFound, "Can't resolve location '" + path + "'");

	return *bestMatch;
}

int LocationProcessor::match(const std::string& remote, const std::string& local)
{
	if (remote.find('*') != std::string::npos)
	{
		// Pattern

		if (algo::match(remote, local))
		{
			int nonStartChars = 0;
			for (int i = 0; i < remote.length(); i++)
				nonStartChars += remote[i] != '*';

			return nonStartChars;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		// Prefix

		if (algo::startsWith(local, remote))
			return (int)remote.length();
		else
			return 0;
	}
}
