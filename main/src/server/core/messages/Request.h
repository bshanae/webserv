#pragma once

#include "string"
#include "map"
#include "utils/templates/Optional.h"
#include "common/RequestMethod.h"
#include "common/HeaderName.h"

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
	const std::map<HeaderName, std::string>& headers() const;
	const std::string& body() const;
	void appendBody(const std::string& bodyPiece);

	Optional<std::string> findHeader(const HeaderName& name) const;
	Optional<size_t> contentLength() const;
	Optional<std::string> hostName() const;
	bool chunkedEncoding() const;

private:

	RequestMethod _method;
	std::string _uri;
	std::string _path;
	std::string _query;
	std::string _protocol;
	std::map<HeaderName, std::string> _headers;
	std::string _body;
};
