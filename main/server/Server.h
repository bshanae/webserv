#pragma once

#include "worker/Worker.h"
#include <string>
#include <sys/poll.h>
#include <vector>

class Server
{
public:
	Server(const std::string& ipAddress, const int port);
	~Server();

	void run();

private:
	int _serverSocket;
	std::vector<struct pollfd> _targets;
	std::vector<Worker> _workers;

	void acceptNewConnection();
};
