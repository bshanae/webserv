#include "Response.h"

#include <ctime>
#include "utils/exceptions/InvalidOperationException.h"

using namespace webserv;

void Response::setStatusCode(const StatusCode code, const std::string& customReason)
{
	std::string finalReason = customReason;
	if (finalReason.empty())
		finalReason = defaultReason(code);

	std::stringstream buffer;
	buffer << "HTTP/1.1 " << code << " " << finalReason;

	_statusLine = buffer.str();
	_statusCode = code;
}

StatusCode Response::getStatusCode() const
{
	return *_statusCode;
}

void Response::setDate(const std::time_t &date)
{
	const std::tm* dateTm = std::gmtime(&date);

	char dateStr[64] = { 0 };
	std::strftime(dateStr, 64, "%a, %d %b %Y %T GMT", dateTm);

	storeHeader(HeaderName::Date, dateStr);
}

void Response::setServer(const std::string& serverName)
{
	storeHeader(HeaderName::Server, serverName);
}

void Response::setLocation(const std::string& location)
{
	storeHeader(HeaderName::Location, location);
}

void Response::addHeader(const std::string& header)
{
	_headers.push_back(header);
}

void Response::setBody(const std::string& data)
{
	_body = data;
	storeHeader(HeaderName::ContentLength, std::to_string(data.length()));
}

void Response::setBody(const MediaType& type, const std::string& data)
{
	setBody(data);
	storeHeader(HeaderName::ContentType, type);
}

bool Response::needsBody() const
{
	return !_body.hasValue();
}

void Response::ignoreBody()
{
	_body = "";
}

std::string Response::build() const
{
	static const std::string endl = "\r\n";

	if (_statusLine.empty())
		throw InvalidOperationException("Status line is empty!");

	std::stringstream buffer;

	buffer << _statusLine << endl;

	for (int i = 0; i < _headers.size(); i++)
		buffer << _headers[i] << endl;

	buffer << endl;

	if (_body.hasValue())
		buffer << *_body;

	return buffer.str();
}

void Response::storeHeader(const HeaderName& name, const std::string& value)
{
	std::stringstream buffer;
	buffer << name << ": " << value;

	_headers.push_back(buffer.str());
}