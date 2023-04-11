#pragma once

#include <string>
#include <set>
#include "utils/templates/Optional.h"
#include "common/RequestMethod.h"

namespace webserv
{
	class Location;
}

std::istream& operator>>(std::istream& source, webserv::Location& config);

class webserv::Location
{
	friend std::istream& ::operator>>(std::istream& source, Location& config);

public:

	const std::string& remotePath() const;
	const std::string& localPath() const;
	const std::string& redirectionUrl() const;
	int redirectionCode() const;
	const std::set<RequestMethod>& methods() const;
	const Optional<std::string> &index() const;
	bool autoindex() const;

	std::string transformRemotePath(const std::string& path) const;

private:

	std::string _remotePath;
	std::string _localPath;
	std::string _redirectionUrl;
	int _redirectionCode;
	std::set<RequestMethod> _methods;
	Optional<std::string> _index;
	bool _autoindex;
};
