#pragma once

#include "string"
#include "sstream"
#include "vector"
#include "common/HeaderName.h"
#include "common/StatusCode.h"
#include "common/MediaType.h"
#include "utils/templates/Optional.h"

namespace webserv
{
	class Response;
}

class webserv::Response
{
public:

	// status line
	void setStatusCode(StatusCode code, const std::string& customReason = "");
	StatusCode getStatusCode() const;

	// header
	void setDate(const std::time_t& date);
	void setServer(const std::string& serverName);
	void setLocation(const std::string& location);
	void addHeader(const std::string& header);

	// body
	void setBody(const std::string& data);
	void setBody(const MediaType& type, const std::string& data);
	bool needsBody() const;
	void ignoreBody();

	std::string build() const;

private:

	Optional<StatusCode> _statusCode; // hack
	std::string _statusLine;
	std::vector<std::string> _headers;
	Optional<std::string> _body;

	void storeHeader(const HeaderName& name, const std::string& value);
};
