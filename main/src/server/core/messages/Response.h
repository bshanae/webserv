#pragma once

#include "string"
#include "sstream"
#include "vector"
#include "common/HeaderType.h"
#include "common/StatusCode.h"
#include "common/MediaType.h"
#include "utils/templates/Optional.h"

class Response
{
public:

	// status line
	void setStatusCode(StatusCode code, const std::string& customReason = "");

	// header
	void setDate(const std::time_t& date);
	void setServer(const std::string& serverName);
	void addHeader(const std::string& header);

	// body
	void setBody(const std::string& data);
	void setBody(const MediaType& type, const std::string& data);
	void setEmptyBody();

	std::string build() const;

private:

	std::string _statusLine;
	std::vector<std::string> _headers;
	Optional<std::string> _body;

	void storeHeader(HeaderType name, const std::string& value);
};
