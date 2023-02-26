#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "../aux/HeaderType.h"
#include "../aux/StatusCode.h"
#include "../aux/MediaType.h"
#include "tools/templates/Optional.h"

class Response
{
public:

	void setStatusCode(StatusCode code, const std::string& customReason = "");
	void setDate(const std::time_t& date);
	void setServer(const std::string& serverName);
	void setBody(MediaType type, const std::string& data);

	std::string build() const;

private:

	std::string _statusLine;
	std::vector<std::string> _headers;
	Optional<std::string> _body;

	void storeHeader(HeaderType name, const std::string& value);
};