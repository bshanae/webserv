#include "ClientSocketController.h"

#include <unistd.h>
#include "log/log.h"
#include "utils/algo/str.h"

using namespace webserv;
using namespace webserv::log;

ClientSocketController::ClientSocketController(sys::FDescriptor socket): _listener(NULL) // NOLINT(cppcoreguidelines-pro-type-member-init)
{
	bindSocket(socket);

	log::i << *this << log::startm << "Initialized." << log::endm;
}

ClientSocketController::~ClientSocketController()
{
	log::i << *this << log::startm << "Uninitialized." << log::endm;
}

void ClientSocketController::setListener(IClientSocketListener* listener)
{
	_listener = listener;
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

		if (_listener != NULL)
			_listener->onClientDisconnected(*this);

		return Optional<std::string>();
	}

	_clientBuffer[byteCount] = '\0';

	std::string m = std::string(_clientBuffer);
	logRequest(m);

	return m;
}

Optional<Request> ClientSocketController::processRequest(const std::string& message)
{
	if (_incompleteRequest.hasValue())
	{
		log::e << *this << log::startm << "Incomplete request. Append." << log::endm;
		_incompleteRequest->appendBody(message);

		if (_incompleteRequest->body().size() < *_incompleteRequest->contentLength())
			return Optional<Request>();

		log::e << *this << log::startm << "Incomplete request. Finish." << log::endm;
		Request request = *_incompleteRequest;
		_incompleteRequest.reset();

		return request;
	}
	else
	{
		Optional<Request> request = Request::parse(message);
		if (!request)
		{
			log::e << *this << log::startm << "Request was not parsed!" << log::endm;
			return Optional<Request>();
		}

		if (request->contentLength())
		{
			log::e << *this << log::startm << "Incomplete request. Start." << log::endm;

			_incompleteRequest = request;
			return Optional<Request>();
		}

		return request;
	}
}

Optional<std::string> ClientSocketController::processResponse(const Request& request)
{
	Optional<Response> r = _listener->onClientSentRequest(*this, request);
	if (!r)
	{
		log::w << *this << log::startm << "No response is provided!" << log::endm;
		return Optional<std::string>();
	}

	const std::string rStr = r->build();
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
	stream << "[ClientSocketController:socket=" << controller.socket() << "]";
	return stream;
}