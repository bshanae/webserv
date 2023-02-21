#pragma once

#include <cstddef>
#include <string>
#include "context/Context.h"

class Worker
{
public:
	Worker(Context& context, int fd);
	Worker(const Worker& that);
	Worker& operator=(const Worker& that);

	bool hasConnection() const;
	void processRequest();

private:
	static const size_t _bufferSize = 30720;

	Context& _context;
	int _fd;

	std::string buildResponse() const;
};