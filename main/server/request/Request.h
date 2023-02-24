#pragma once

#include <string>
#include "requestMethod/RequestMethod.h"

class Request
{
public:

	static Request parse(const std::string& data);

	Request(const Request& that);
	Request& operator=(const Request& that);

	RequestMethod getMethod() const;
	std::string getUrl() const;
	std::string getHttpVersion() const;

private:

	RequestMethod _method;
	std::string _url;
	std::string _httpVersion;

	Request(RequestMethod type, const std::string& url, const std::string& httpVersion);
};
