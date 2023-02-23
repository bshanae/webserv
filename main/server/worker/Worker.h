#pragma once

#include <cstddef>
#include <string>
#include "context/VirtualServer.hpp"
//#include "../../Include_main.hpp"
class Worker
{
public:
	Worker(VirtualServer& context, int fd);
	Worker(const Worker& that);
	Worker& operator=(const Worker& that);

	bool hasConnection() const;
	void processRequest();

private:
	static const size_t _bufferSize = 30720;

	VirtualServer& _context;
	int _fd;

	std::string buildResponse() const;
};