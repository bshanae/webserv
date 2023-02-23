#include "Request.h"
#include <iostream>
Request Request::parse(const std::string& data)
{
	std::cout << data << std::endl;
	return Request(GET, "", "1.1");
}

Request::Request(const Request& that)
{
	_type = that._type;
	_url = that._url;
	_httpVersion = that._httpVersion;
}

Request& Request::operator=(const Request& that)
{
	_type = that._type;
	_url = that._url;
	_httpVersion = that._httpVersion;

	return *this;
}

Request::Type Request::getType() const
{
	return _type;
}

std::string Request::getUrl() const
{
	return _url;
}

std::string Request::getHttpVersion() const
{
	return _httpVersion;
}

Request::Request(const Type type, const std::string& url, const std::string& httpVersion) :
	_type(type),
	_url(url),
	_httpVersion(httpVersion)
{
}
