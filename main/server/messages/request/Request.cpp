#include "Request.h"

#include <sstream>

Request Request::parse(const std::string& data)
{
	std::stringstream stream(data);

	RequestMethod method;
	stream >> method;

	std::string uri;
	stream >> uri;

	return Request(method, uri, "HTTP/1.1");
}

RequestMethod Request::getMethod() const
{
	return _method;
}

const std::string& Request::getUri() const
{
	return _uri;
}

const std::string& Request::getPath() const
{
	return _path;
}

const std::string& Request::getQuery() const
{
	return _query;
}

const std::string& Request::getProtocol() const
{
	return _protocol;
}

Request::Request(RequestMethod method, const std::string& uri, const std::string& protocol) :
	_method(method), _uri(uri), _protocol(protocol)
{
	const size_t iQuestion = uri.find('?');
	if (iQuestion != std::string::npos)
	{
		_path = uri.substr(0, iQuestion);
		_query = uri.substr(iQuestion + 1, uri.length() - 1);
	}
	else
	{
		_path = uri;
		_query = "";
	}
}