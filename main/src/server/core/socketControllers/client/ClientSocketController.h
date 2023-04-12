#pragma once

#include <vector>
#include "server/core/messages/Request.h"
#include "server/core/messages/Response.h"
#include "server/core/socketControllers/SocketController.h"
#include "server/core/socketDelegates/IClientSocketDelegate.h"
#include "RequestAccumulator.h"


namespace webserv
{
	class ClientSocketController;
}

std::ostream& operator<<(std::ostream& stream, const webserv::ClientSocketController& controller);

class webserv::ClientSocketController : public SocketController
{
	friend std::ostream& ::operator<<(std::ostream& stream, const ClientSocketController& controller);

public:

	explicit ClientSocketController(sys::FDescriptor socket, const WebAddress& address);
	virtual ~ClientSocketController();

	const WebAddress& address() const;
	void setDelegate(IClientSocketDelegate* delegate);

private:

	static const size_t _clientBufferSize = 8192;

	WebAddress _address;
	char _clientBuffer[_clientBufferSize];
	IClientSocketDelegate* _delegate;
	RequestAccumulator _requestAccumulator;

	virtual void processSocketEvent();

	Optional<std::string> readMessageFromSocket();
	Optional<Request> processRequest(const std::string& message);
	Optional<std::string> processResponse(const Request& request);
	void writeMessageToSocket(const std::string& message);

	void logRequest(const std::string& str) const;
	void logResponse(const std::string& str) const;
};
