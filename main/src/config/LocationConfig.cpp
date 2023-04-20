#include "LocationConfig.h"

#include "utils/algo/str.h"
#include "utils/sys/sys.path.h"
#include "common/path.h"
#include "config/utils.h"

using namespace webserv;
using namespace webserv::config;

std::istream& operator>>(std::istream& source, webserv::config::LocationConfig& config)
{
	std::string line;
	while (utils::getLine(source, line))
	{
		if (utils::isIgnored(line))
		{
		}
		else if (utils::isBlockEnd(line))
		{
			break;
		}
		else if (algo::startsWith(line, "remote"))
		{
			config._remotePath = directoryRemoteView(utils::extractArgument(line));
		}
		else if (algo::startsWith(line, "local"))
		{
			config._localPath = directoryRemoteView(utils::extractArgument(line));
		}
		else if (algo::startsWith(line, "redirect"))
		{
			std::vector<std::string> args = utils::extractArguments<std::string>(line);
			config._redirectionCode = utils::convert<int>(args[0]);
			config._redirectionUrl = args[1];
		}
		else if (algo::startsWith(line, "methods"))
		{
			std::vector<RequestMethod> v = utils::extractArguments<RequestMethod>(line);
			config._methods = std::set<RequestMethod>(v.begin(), v.end());
		}
		else if (algo::startsWith(line, "extensions"))
		{
			std::vector<std::string> v = utils::extractArguments<std::string>(line);
			config._extensions = std::set<std::string>(v.begin(), v.end());
		}
		else if (algo::startsWith(line, "index"))
		{
			config._index = utils::extractArgument(line);
		}
		else if (algo::startsWith(line, "autoindex"))
		{
			config._autoindex = true;
		}
		else if (algo::startsWith(line, "cgi_enable"))
		{
			config._cgiEnabled = true;
		}
		else if (algo::startsWith(line, "cgi_forward"))
		{
			config._cgiForward = utils::extractArgument<std::string>(line);
		}
		else if (algo::startsWith(line, "max_client_body_size"))
		{
			config._maxClientBodySize = utils::extractArgument<size_t>(line);
		}
		else
		{
			throw ParsingException("Invalid line: " + line);
		}
	}

	return source;
}

const std::string& LocationConfig::remotePath() const
{
	return _remotePath;
}

const std::string& LocationConfig::localPath() const
{
	return _localPath;
}

const std::string& LocationConfig::redirectionUrl() const
{
	return _redirectionUrl;
}

int LocationConfig::redirectionCode() const
{
	return _redirectionCode;
}

const std::set<RequestMethod>& LocationConfig::methods() const
{
	return _methods;
}

const Optional<std::set<std::string> >& LocationConfig::extensions() const
{
	return _extensions;
}

const Optional<std::string> &LocationConfig::index() const
{
	return _index;
}

bool LocationConfig::autoindex() const
{
	return _autoindex;
}

bool LocationConfig::cgiEnabled() const
{
	return _cgiEnabled;
}

const Optional<std::string>& LocationConfig::cgiForward() const
{
	return _cgiForward;
}

const Optional<size_t>& LocationConfig::maxClientBodySize() const
{
	return _maxClientBodySize;
}

std::string LocationConfig::transformRemotePath(const std::string& path) const
{
	if (_remotePath.find('*') != std::string::npos)
	{
		return sys::path::concat(_localPath, sys::path::file(path));
	}
	else
	{
		const std::string suffix = algo::range(path, _remotePath.length(), path.length());
		return sys::path::concat(_localPath, suffix);
	}
}