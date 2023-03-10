#pragma once

#include <vector>
#include "SocketController.h"
#include "server/core/messages/Request.h"
#include "server/core/messages/Response.h"

class ClientSocketController;

class IClientSocketListener
{
public:

	virtual void onClientDisconnected(const ClientSocketController& controller) = 0;
	virtual Optional<Response> onClientSentRequest(const ClientSocketController& controller, const Request& request) = 0;
};

class ClientSocketController : public SocketController
{
	friend std::ostream& operator<<(std::ostream& stream, const ClientSocketController& controller);

public:

	explicit ClientSocketController(sys::FDescriptor socket);
	virtual ~ClientSocketController();

	void setListener(IClientSocketListener* listener);

private:

	static const size_t _clientBufferSize = 8192;

	char _clientBuffer[_clientBufferSize];
	IClientSocketListener* _listener;

	virtual void processSocketEvent();
	void logRequest(const std::string& str) const;
	void logResponse(const std::string& str) const;
};
