#pragma once

#include <string>
#include "common/WebAddress.h"
#include "CGIConfig.h"

namespace webserv
{
	namespace config
	{
		class VirtualServerConfig;
	}
}

class webserv::config::VirtualServerConfig
{
public:

	std::string root() const;
	WebAddress address() const;
	bool autoindex() const;
	CGIConfig cgi() const;
};
