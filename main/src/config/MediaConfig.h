#pragma once

#include <unordered_map>
#include <string>
#include "common/MediaType.h"

class MediaConfig
{
public:

	MediaConfig();

	const std::unordered_map<std::string, MediaType> &fileExtensionToMediaType() const;

private:

	std::unordered_map<std::string, MediaType> _fileExtensionToMediaType;
};
