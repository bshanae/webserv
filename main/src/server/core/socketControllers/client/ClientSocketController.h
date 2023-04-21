#pragma once

#include <vector>
#include "utils/templates/SimpleBuffer.h"
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

	ClientSocketController(sys::FDescriptor socket, const WebAddress& address);
	virtual ~ClientSocketController();

	const WebAddress& address() const;
	void setDelegate(IClientSocketDelegate* delegate);

private:

	SimpleBuffer<char> _readBuffer;
	SimpleBuffer<char> _writeBuffer;
	WebAddress _address;
	IClientSocketDelegate* _delegate;
	RequestAccumulator _requestAccumulator;

	ClientSocketController(ClientSocketController&);
	ClientSocketController& operator=(ClientSocketController&);

	virtual void processSocketEvent(SocketEvent event);
	void processCanReadEvent();
	void processCanWriteEvent();
	Optional<std::string> readFromSocket();
	Optional<Request> processRequest(const std::string& data);
	Optional<std::string> processResponse(const Optional<Request>& request);
	void saveResponse(const std::string& message);
	void flushResponses();

	void logRequest(const std::string& str) const;
	void logResponse(const std::string& str) const;
};
