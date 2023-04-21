#include "ServerSocketController.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include "log/log.h"
#include "utils/algo/str.h"
#include "utils/exceptions/SocketException.h"

using namespace webserv;

ServerSocketController::ServerSocketController(const WebAddress& address) : _address(address)
{
	sys::FDescriptor s = ::socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
		throw SocketException("Socket creation error.");

	if (fcntl(s, F_SETFL, O_NONBLOCK) != 0)
		throw SocketException("Can't set O_NONBLOCK!");

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
	_clientControllers.clear();
	log::i << *this << log::startm << "Uninitialized." << log::endm;
}

void ServerSocketController::registerDelegate(IServerSocketDelegate* delegate)
{
	_delegates.push_back(delegate);
}

void ServerSocketController::processSocketEvent(SocketEvent event)
{
	struct sockaddr_in clientAddress = {};
	uint32_t addressLength;
	int s = accept(socket(), reinterpret_cast<sockaddr*>(&clientAddress), &addressLength);
	if (s < 0)
		throw SocketException("accept fail");

	char clientAddressStr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(clientAddress.sin_addr), clientAddressStr, INET_ADDRSTRLEN);

	if (fcntl(s, F_SETFL, O_NONBLOCK) != 0)
		throw SocketException("fcntl fail");

	ClientSocketController* clientController = new ClientSocketController(s, WebAddress(clientAddressStr, clientAddress.sin_port));
	_clientControllers.push_back(clientController);

	clientController->setDelegate(this);
	notifyAboutNewController(clientController);
}

void ServerSocketController::onClientDisconnected(const WebAddress& clientAddress)
{
	for (std::vector<ClientSocketController*>::iterator i = _clientControllers.begin(); i != _clientControllers.end(); i++)
	{
		if ((*i)->address() == clientAddress)
		{
			_clientControllers.erase(i);
			return;
		}
	}

	log::e << *this << log::startm << "Can't find client controller with address" << clientAddress << "!" << log::endm;
}

Response ServerSocketController::respondToRequest(const Optional<Request>& request)
{
	if (request)
	{
		for (std::vector<IServerSocketDelegate*>::iterator i = _delegates.begin(); i != _delegates.end(); i++)
		{
			if ((*i)->targetOfRequest(*request))
				return (*i)->respondToRequest(*request);
		}
	}

	return _delegates.front()->respondToRequest(request);
}

std::ostream& operator<<(std::ostream& stream, const ServerSocketController& controller)
{
	stream << "[ServerSocketController:address=" << controller._address << ",socket=" << controller.socket() << "]";
	return stream;
}