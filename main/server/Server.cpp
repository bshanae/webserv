#include "Server.h"

#include "tools/exceptions/SocketException.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "tools/log/log.h"
#include "tools/sys/sys.h"

Server::Server(Context &context): _context(context)
{
	log::i << log::entity << "Server" << log::endl
		   << "Startup." << log::endm;

	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocket < 0)
		throw SocketException("Socket creation error.");

	const int port = context.getConfig().getServerPort();
	const std::string address = context.getConfig().getServerAddress();

	const struct sockaddr_in socketAddress = {
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr = {
			.s_addr = inet_addr(address.c_str())
		}
	};

	if (bind(_serverSocket, reinterpret_cast<const sockaddr*>(&socketAddress), sizeof(socketAddress)) < 0)
		throw SocketException("Bind fail.");

	if (listen(_serverSocket, 32) < 0)
		throw SocketException("Listen fail.");
}

Server::~Server()
{
	log::i << log::entity << "Server" << log::endl
		   << "Shutdown." << log::endm;

	close(_serverSocket);
}

void Server::run()
{
	_targets.push_back((struct pollfd){ .fd = _serverSocket, .events = POLLRDNORM });

	while (!sys::TerminationRequested)
	{
		int readyCount = poll(_targets.data(), _targets.size(), 0);
		// TODO Check error
		if (readyCount == 0)
			continue;

		if (_targets[0].revents & POLLRDNORM)
		{
			acceptNewConnection();
			readyCount--;
		}

		for (int i = 1; i < _targets.size() && readyCount > 0; i++)
		{
			const struct pollfd& target = _targets[i];
			if (!(target.revents & (POLLRDNORM | POLLERR)))
				continue;

			Worker& worker = _workers[i - 1];
			worker.onRequestReceived();

			if (!worker.hasConnection())
			{
				_targets.erase(_targets.begin() + i);
				_workers.erase(_workers.begin() + i - 1);

				i--;
			}

			readyCount--;
		}
	}

	log::i << log::entity << "Server" << log::endl
		   << "Terminating..." << log::endm;
}

void Server::acceptNewConnection()
{
	struct sockaddr_in clientSocketAddress = {};
	uint32_t clientSocketAddressLength;
	int clientSocket = accept(_serverSocket, reinterpret_cast<sockaddr*>(&clientSocketAddress), &clientSocketAddressLength);
	// TODO if (tempSocket < 0)

	_targets.push_back((struct pollfd){ .fd = clientSocket, .events = POLLRDNORM });
	_workers.push_back(Worker(_context, clientSocket));
	// TODO LIMIT
}