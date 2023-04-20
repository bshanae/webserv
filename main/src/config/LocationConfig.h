#pragma once

#include <string>
#include <set>
#include "utils/templates/Optional.h"
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
	const std::string& redirectionUrl() const;
	int redirectionCode() const;
	const std::set<RequestMethod>& methods() const;
	const Optional<std::set<std::string> >& extensions() const;
	const Optional<std::string> &index() const;
	bool autoindex() const;
	bool cgiEnabled() const;
	const Optional<std::string>& cgiForward() const;

	std::string transformRemotePath(const std::string& path) const;

private:

	std::string _remotePath;
	std::string _localPath;
	std::string _redirectionUrl;
	int _redirectionCode;
	std::set<RequestMethod> _methods;
	Optional<std::set<std::string> > _extensions;
	Optional<std::string> _index;
	bool _autoindex;
	bool _cgiEnabled;
	Optional<std::string> _cgiForward;
};
