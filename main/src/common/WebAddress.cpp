#include "WebAddress.h"

#include <string>
#include <sstream>
#include "utils/exceptions/ParsingException.h"

using namespace webserv;

WebAddress::WebAddress() : port(-1)
{
}

WebAddress::WebAddress(const std::string& host, int port) : host(host), port(port)
{
}

bool WebAddress::operator==(const WebAddress& that) const
{
	return this->host == that.host && this->port == that.port;
}

bool WebAddress::operator<(const WebAddress& r) const
{
	if (this->host != r.host)
		return this->host < r.host;

	return this->port < r.port;
}

std::istream& operator>>(std::istream& stream, WebAddress& address)
{
	std::string line;
	if (!(stream >> line))
		throw ParsingException("Can't parse WebAddress");

	const size_t colon = line.find(':');
	if (colon == -1)
	{
		address.host = line;
	}
	else
	{
		address.host = line.substr(0, colon);
		address.port = std::stoi(line.substr(colon + 1, line.length()));
	}

	return stream;
}

std::ostream& operator<<(std::ostream& stream, const WebAddress& address)
{
	stream << address.host << ":" << address.port;
	return stream;
}