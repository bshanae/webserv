#pragma once

#include "common/WebAddress.h"
#include "server/core/messages/Request.h"
#include "server/core/messages/Response.h"

namespace webserv
{
	class IClientSocketDelegate;
}
class webserv::IClientSocketDelegate
{
public:

	virtual ~IClientSocketDelegate() {}

	virtual void onClientDisconnected(const WebAddress& address) = 0;
	virtual Response respondToRequest(const Request& request) = 0;
};