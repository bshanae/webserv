#include "Location.h"

#include "utils/algo/str.h"
#include "utils/sys/sys.path.h"
#include "config/utils.h"

using namespace webserv;
using namespace webserv::config;

std::istream& operator>>(std::istream& source, webserv::Location& config)
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
			config._remotePath = utils::extractArgument(line);
		}
		else if (algo::startsWith(line, "local"))
		{
			config._localPath = utils::extractArgument(line);
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
	}

	return source;
}

const std::string& Location::remotePath() const
{
	return _remotePath;
}

const std::string& Location::localPath() const
{
	return _localPath;
}

const std::string& Location::redirectionUrl() const
{
	return _redirectionUrl;
}

int Location::redirectionCode() const
{
	return _redirectionCode;
}

const std::set<RequestMethod>& Location::methods() const
{
	return _methods;
}

std::string Location::transformRemotePath(const std::string& path) const
{
	const std::string suffix = algo::range(path, _remotePath.length(), path.length());
	return sys::path::concat(_localPath, suffix);
}