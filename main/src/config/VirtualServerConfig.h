#pragma once

#include <string>
#include "common/WebAddress.h"
#include "CGIConfig.h"

class VirtualServerConfig
{
public:

	std::string root() const;
	WebAddress address() const;
	bool autoindex() const;
	CGIConfig cgi() const;
};
