#pragma once

#include <vector>
#include "SocketController.h"
#include "ClientSocketController.h"
#include "common/WebAddress.h"
#include "server/core/messages/Response.h"
#include "utils/templates/Optional.h"

class IServerSocketListener
{
public:

	virtual Optional<Response> onServerReceivedRequest(const Request& request) = 0;
};

class ServerSocketController : public SocketController, public IClientSocketListener
{
	friend std::ostream& operator<<(std::ostream& stream, const ServerSocketController& controller);

public:

	explicit ServerSocketController(const WebAddress& address);
	~ServerSocketController();

	void registerListener(IServerSocketListener& listener);

private:

	WebAddress _address;
	std::vector<ClientSocketController*> _clientControllers;
	std::vector<IServerSocketListener*> _listeners;

	virtual void processSocketEvent();
	virtual void onClientDisconnected(const ClientSocketController& clientC);
	virtual Optional<Response> onClientSentRequest(const ClientSocketController& clientC, const Request& request);
};