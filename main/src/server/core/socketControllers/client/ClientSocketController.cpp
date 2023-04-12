#include "ClientSocketController.h"

#include <unistd.h>
#include "log/log.h"
#include "utils/algo/str.h"

using namespace webserv;
using namespace webserv::log;

ClientSocketController::ClientSocketController(sys::FDescriptor socket, const WebAddress& address): _delegate(NULL), _address(address) // NOLINT(cppcoreguidelines-pro-type-member-init)
{
	bindSocket(socket);

	log::i << *this << log::startm << "Initialized." << log::endm;
}

ClientSocketController::~ClientSocketController()
{
	log::i << *this << log::startm << "Uninitialized." << log::endm;
}

const WebAddress& ClientSocketController::address() const
{
	return _address;
}

void ClientSocketController::setDelegate(IClientSocketDelegate* delegate)
{
	_delegate = delegate;
}

void ClientSocketController::processSocketEvent()
{
	Optional<std::string> message = readMessageFromSocket();
	if (!message)
		return;

	Optional<Request> request = processRequest(*message);
	if (!request)
		return;

	Optional<std::string> response = processResponse(*request);
	if (!response)
		return;

	writeMessageToSocket(*response);
}

Optional<std::string> ClientSocketController::readMessageFromSocket()
{
	// TODO What is buffer is too small?
	ssize_t byteCount = read(socket(), _clientBuffer, _clientBufferSize - 1);
	if (byteCount <= 0)
	{
		log::w << *this << log::startm << "Connection closed." << log::endm;

		unbindSocket();

		if (_delegate != NULL)
			_delegate->onClientDisconnected(_address);

		return Optional<std::string>();
	}

	_clientBuffer[byteCount] = '\0';

	std::string m = std::string(_clientBuffer);
	logRequest(m);

	return m;
}

Optional<Request> ClientSocketController::processRequest(const std::string& message)
{
	_requestAccumulator.accumulate(message);

	if (_requestAccumulator.requestReady())
		return _requestAccumulator.request();
	else
		return Optional<Request>();
}

Optional<std::string> ClientSocketController::processResponse(const Request& request)
{
	Response r = _delegate->respondToRequest(request);

	const std::string rStr = r.build();
	logResponse(rStr);

	return rStr;
}

void ClientSocketController::writeMessageToSocket(const std::string& message)
{
	const long bytesSent = write(socket(), message.c_str(), message.size());
	if (bytesSent != message.size())
	{
		// TODO Error
	}
}

void ClientSocketController::logRequest(const std::string& str) const
{
	if (!log::v.enabled)
		return;

	std::string markedStr = algo::truncate(str, 5000);
	algo::markEmptyLines(markedStr, "\r\n");

	log::v << *this << log::startm << "REQUEST" << log::endl
		   << markedStr << log::endm;
}

void ClientSocketController::logResponse(const std::string& str) const
{
	if (!log::v.enabled)
		return;

	std::string markedStr = algo::truncate(str, 500);
	algo::markEmptyLines(markedStr, "\r\n");

	log::v << *this << log::startm << "RESPONSE" << log::endl
		   << markedStr << log::endm;
}

std::ostream& operator<<(std::ostream& stream, const ClientSocketController& controller)
{
	stream << "[ClientSocketController:socket=" << controller.socket() << ",address=" << controller._address << "]";
	return stream;
}