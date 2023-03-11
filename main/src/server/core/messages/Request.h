#pragma once

#include "string"
#include "map"
#include "common/RequestMethod.h"
#include "utils/templates/Optional.h"

namespace webserv
{
	class Request;
}

class webserv::Request
{
public:

	static Optional<Request> parse(const std::string& data);

	RequestMethod method() const;
	const std::string& uri() const;
	const std::string& path() const;
	const std::string& query() const;
	const std::string& protocol() const;

private:

	RequestMethod _method;
	std::string _uri;
	std::string _path;
	std::string _query;
	std::string _protocol;

	Request(RequestMethod method, const std::string& url, const std::string& protocol);
};
