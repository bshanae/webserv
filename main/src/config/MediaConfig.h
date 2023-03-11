#pragma once

#include <unordered_map>
#include <string>
#include "common/MediaType.h"

namespace webserv
{
	namespace config
	{
		class MediaConfig;
	}
}

class webserv::config::MediaConfig
{
public:

	MediaConfig();

	const std::unordered_map<std::string, MediaType>& fileExtensionToMediaType() const;

private:

	std::unordered_map<std::string, MediaType> _fileExtensionToMediaType;
};