#pragma once

#include <string>
#include <map>
#include "../aux/RequestMethod.h"

class Request
{
public:

	static Request parse(const std::string& data);

	Request(const Request& that);
	Request& operator=(const Request& that);

	RequestMethod getMethod() const;
	const std::string& getUri() const;
	const std::string& getPath() const;
	const std::string& getQuery() const;
	const std::string& getProtocol() const;

private:

	RequestMethod _method;
	std::string _uri;
	std::string _path;
	std::string _query;
	std::string _protocol;

	Request(RequestMethod method, const std::string& url, const std::string& protocol);
};
