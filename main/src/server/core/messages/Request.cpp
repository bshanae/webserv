#include "Request.h"

#include <sstream>

using namespace webserv;

Optional<Request> Request::parse(const std::string& data)
{
	std::stringstream stream(data);

	RequestMethod method;
	stream >> method;

	std::string uri;
	stream >> uri;

	return Request(method, uri, "HTTP/1.1");
}

RequestMethod Request::method() const
{
	return _method;
}

const std::string& Request::uri() const
{
	return _uri;
}

const std::string& Request::path() const
{
	return _path;
}

const std::string& Request::query() const
{
	return _query;
}

const std::string& Request::protocol() const
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