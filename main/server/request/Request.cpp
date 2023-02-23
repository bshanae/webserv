#include "Request.h"

Request Request::parse(const std::string& data)
{
	return Request(GET, "/sample1.http", "1.1");
}

Request::Request(const Request& that)
{
	_method = that._method;
	_url = that._url;
	_httpVersion = that._httpVersion;
}

Request& Request::operator=(const Request& that)
{
	_method = that._method;
	_url = that._url;
	_httpVersion = that._httpVersion;

	return *this;
}

Request::Method Request::getMethod() const
{
	return _method;
}

std::string Request::getUrl() const
{
	return _url;
}

std::string Request::getHttpVersion() const
{
	return _httpVersion;
}

Request::Request(const Method type, const std::string& url, const std::string& httpVersion) :
	_method(type),
	_url(url),
	_httpVersion(httpVersion)
{
}
