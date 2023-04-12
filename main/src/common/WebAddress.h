#pragma once

#include <string>

namespace webserv
{
	struct WebAddress;
}

struct webserv::WebAddress
{
	std::string host;
	int port;

	WebAddress();
	WebAddress(const std::string& host, int port);

	bool operator==(const WebAddress& that) const;
	bool operator<(const WebAddress& r) const;
};

std::istream& operator>>(std::istream& stream, webserv::WebAddress& address);
std::ostream& operator<<(std::ostream& stream, const webserv::WebAddress& address);