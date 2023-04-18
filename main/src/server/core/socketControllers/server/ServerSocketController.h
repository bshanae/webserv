#pragma once

#include <vector>
#include "server/core/socketDelegates/IServerSocketDelegate.h"
#include "server/core/socketControllers/SocketController.h"
#include "server/core/socketControllers/client/ClientSocketController.h"
#include "common/WebAddress.h"
#include "server/core/messages/Response.h"
#include "utils/templates/Optional.h"

namespace webserv
{
	class ServerSocketController;
}

std::ostream& operator<<(std::ostream& stream, const webserv::ServerSocketController& controller);

class webserv::ServerSocketController : public SocketController, public IClientSocketDelegate
{
	friend std::ostream& ::operator<<(std::ostream& stream, const ServerSocketController& controller);

public:

	explicit ServerSocketController(const WebAddress& address);
	virtual ~ServerSocketController();

	void registerDelegate(IServerSocketDelegate* listener);

private:

	WebAddress _address;
	std::vector<ClientSocketController*> _clientControllers;
	std::vector<IServerSocketDelegate*> _delegates;

	virtual void processSocketEvent(SocketEvent event);
	virtual void onClientDisconnected(const WebAddress& clientAddress);
	virtual Response respondToRequest(const webserv::Request& request);
};