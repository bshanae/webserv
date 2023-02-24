#pragma once

#include <string>
#include <sys/poll.h>
#include <vector>
#include "context/Context.h"
#include "worker/Worker.h"
class Server
{
public:
	explicit Server(Context &context);
	~Server();

	void run();

private:
	Context & _context;
	int _serverSocket;
	std::vector<struct pollfd> _targets;
	std::vector<Worker> _workers;

	void acceptNewConnection();
};
