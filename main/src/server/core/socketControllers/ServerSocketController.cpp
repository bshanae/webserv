#include "ServerSocketController.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "log/log.h"
#include "utils/algo/str.h"
#include "utils/exceptions/SocketException.h"

ServerSocketController::ServerSocketController(const WebAddress& address) : _address(address)
{
	sys::FDescriptor s = ::socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
		throw SocketException("Socket creation error.");

	int opt = 1;
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw SocketException("Can't set SO_REUSEADDR!");

	const struct sockaddr_in socketAddress = {
		.sin_family = AF_INET,
		.sin_port = htons(_address.port),
		.sin_addr = {
			.s_addr = inet_addr(_address.host.c_str())
		}
	};

	if (bind(s, reinterpret_cast<const sockaddr*>(&socketAddress), sizeof(socketAddress)) < 0)
		throw SocketException("Bind fail.");

	if (listen(s, 32) < 0)
		throw SocketException("Listen fail.");

	bindSocket(s);

	log::i << *this << log::startm << "Initialized." << log::endm;
}

ServerSocketController::~ServerSocketController()
{
	for (int i = 0; i < _clientControllers.size(); i++)
		delete _clientControllers[i];

	log::i << *this << log::startm << "Uninitialized." << log::endm;
}

void ServerSocketController::registerListener(IServerSocketListener& listener)
{
	_listeners.push_back(&listener);
}

void ServerSocketController::processSocketEvent()
{
	struct sockaddr_in clientAddress = {};
	uint32_t addressLength;
	int s = accept(socket(), reinterpret_cast<sockaddr*>(&clientAddress), &addressLength);
	// TODO if (tempSocket < 0)

	ClientSocketController* clientController = new ClientSocketController(s);
	_clientControllers.push_back(clientController);

	clientController->setListener(this);
	notifyAboutNewController(clientController);
}

void ServerSocketController::onClientDisconnected(const ClientSocketController& clientC)
{
	for (std::vector<ClientSocketController*>::iterator i = _clientControllers.begin(); i != _clientControllers.end(); i++)
	{
		if (*i == &clientC)
		{
			delete *i;
			_clientControllers.erase(i);

			return;
		}
	}

	log::e << *this << log::startm << "Can't find client controller " << clientC << "!" << log::endm;
}

Optional<Response> ServerSocketController::onClientSentRequest(const ClientSocketController& clientC, const Request& request)
{
	Optional<Response> response;

	for (std::vector<IServerSocketListener*>::iterator i = _listeners.begin(); i != _listeners.end(); i++)
	{
		response = (*i)->onServerReceivedRequest(request);
		if (response)
			break;
	}

	return response;
}

std::ostream& operator<<(std::ostream& stream, const ServerSocketController& controller)
{
	stream << "[ServerSocketController:address=" << controller._address << ",socket=" << controller.socket() << "]";
	return stream;
}