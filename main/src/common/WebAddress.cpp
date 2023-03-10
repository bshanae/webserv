#include "WebAddress.h"

#include <string>
#include <sstream>

WebAddress::WebAddress() : port(-1)
{
}

WebAddress::WebAddress(const std::string& host, int port) : host(host), port(port)
{
}

bool WebAddress::operator<(const WebAddress& r) const
{
	if (this->host != r.host)
		return this->host < r.host;

	return this->port < r.port;
}

std::ostream& operator<<(std::ostream& stream, const WebAddress& address)
{
	stream << address.host << ":" << address.port;
	return stream;
}