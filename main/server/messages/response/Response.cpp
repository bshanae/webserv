#include "Response.h"

#include <ctime>
#include "tools/exceptions/InvalidOperationException.h"

void Response::setStatusCode(const StatusCode code, const std::string& customReason)
{
	std::string finalReason = customReason;
	if (finalReason.empty())
		finalReason = defaultReason(code);

	std::stringstream buffer;
	buffer << "HTTP/1.1 " << code << " " << finalReason;

	_statusLine = buffer.str();
}

void Response::setDate(const std::time_t &date)
{
	const std::tm* dateTm = std::gmtime(&date);

	char dateStr[64] = { 0 };
	std::strftime(dateStr, 64, "%a, %d %b %Y %T GMT", dateTm);

	storeHeader(HeaderTypeDate, dateStr);
}

void Response::setServer(const std::string& serverName)
{
	storeHeader(HeaderTypeServer, serverName);
}

void Response::addHeader(const std::string& header)
{
	_headers.push_back(header);
}

void Response::setBody(const std::string& data)
{
	_body = data;
	storeHeader(HeaderTypeContentLength, std::to_string(data.length()));
}

void Response::setBody(const MediaType& type, const std::string& data)
{
	setBody(data);
	storeHeader(HeaderTypeContentType, type);
}

void Response::setEmptyBody()
{
	setBody(MediaType::Default, "");
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

	if (!_body.hasValue())
		throw InvalidOperationException("Response's body has to be set in order to fill header Content-Length!");

	buffer << *_body;

	return buffer.str();
}

void Response::storeHeader(const HeaderType name, const std::string& value)
{
	std::stringstream buffer;
	buffer << toString(name) << ": " << value;

	_headers.push_back(buffer.str());
}