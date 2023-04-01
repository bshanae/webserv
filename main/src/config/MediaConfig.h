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

std::istream& operator>>(std::istream& source, webserv::config::MediaConfig& config);

class webserv::config::MediaConfig
{
	friend std::istream& ::operator>>(std::istream& source, webserv::config::MediaConfig& config);

public:

	static MediaConfig makeDefault();

	const std::unordered_map<std::string, MediaType>& fileExtensionToMediaType() const;

private:

	std::unordered_map<std::string, MediaType> _fileExtensionToMediaType;
};