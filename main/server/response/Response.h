#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "headerType/HTTPHeaderType.h"
#include "statusCode/HTTPStatusCode.h"
#include "mediaType/HttpMediaType.h"
#include "tools/templates/Optional.h"

class Response
{
public:

	void setStatusCode(HTTPStatusCode code, const std::string& customReason = "");
	void setDate(const std::time_t& date);
	void setServer(const std::string& serverName);
	void setBody(HttpMediaType type, const std::string& data);

	std::string build() const;

private:

	std::string _statusLine;
	std::vector<std::string> _headers;
	Optional<std::string> _body;

	void storeHeader(HTTPHeaderType name, const std::string& value);
};
