#pragma once

#include <string>
#include <set>
#include "common/RequestMethod.h"

namespace webserv
{
	namespace config
	{
		class LocationConfig;
	}
}

std::istream& operator>>(std::istream& source, webserv::config::LocationConfig& config);

class webserv::config::LocationConfig
{
	friend std::istream& ::operator>>(std::istream& source, LocationConfig& config);

public:

	const std::string& remotePath() const;
	const std::string& localPath() const;
	const std::set<RequestMethod>& methods() const;

private:

	std::string _remotePath;
	std::string _localPath;
	std::set<RequestMethod> _methods;
};
