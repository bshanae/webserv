#pragma once

#include <vector>
#include "server/core/messages/Request.h"
#include "server/core/messages/Response.h"

namespace webserv
{
	class IServerSocketDelegate;
}

class webserv::IServerSocketDelegate
{
public:

	virtual ~IServerSocketDelegate() {}

	virtual bool targetOfRequest(const Request& request) = 0;
	virtual Response respondToRequest(const Request& request) = 0;
};