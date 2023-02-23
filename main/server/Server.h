#pragma once

#include <string>
#include <sys/poll.h>
#include <vector>
#include "context/Context.h"
#include "worker/Worker.h"
#include "../Include_main.hpp"
class Server
{
public:
	explicit Server(serv_stor &context);
	~Server();

	void run();

private:
	serv_stor & _context;
	int _serverSocket;
	std::vector<struct pollfd> _targets;
	std::vector<Worker> _workers;

	void acceptNewConnection();
};
