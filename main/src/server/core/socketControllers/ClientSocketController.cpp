#include "ClientSocketController.h"

#include <unistd.h>
#include "log/log.h"
#include "utils/algo/str.h"

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
	// TODO What is buffer is too small?
	ssize_t byteCount = read(socket(), _clientBuffer, _clientBufferSize - 1);
	if (byteCount <= 0)
	{
		log::w << *this << log::startm << "Connection closed." << log::endm;

		unbindSocket();

		if (_listener != NULL)
			_listener->onClientDisconnected(*this);

		return;
	}

	_clientBuffer[byteCount] = '\0';

	const std::string requestStr = std::string(_clientBuffer);
	logRequest(requestStr);

	Optional<Request> request = Request::parse(requestStr);
	if (!request)
	{
		log::e << *this << log::startm << "Request can't be parsed!" << log::endm;
		return;
	}

	Optional<Response> response = _listener->onClientSentRequest(*this, *request);
	if (!response)
	{
		log::w << *this << log::startm << "No response is provided!" << log::endm;
		return;
	}

	const std::string responseStr = response->build();
	logResponse(responseStr);

	const long bytesSent = write(socket(), responseStr.c_str(), responseStr.size());
	if (bytesSent != responseStr.size())
	{
		// TODO Error
	}
}

void ClientSocketController::logRequest(const std::string& str) const
{
	if (!log::v.enabled)
		return;

	std::string markedStr = algo::truncate(str, 500);
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