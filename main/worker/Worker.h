#pragma once

#include <cstddef>
#include <string>

class Worker
{
public:
	Worker(int fd);

	bool hasConnection() const;
	void processRequest();

private:
	static const size_t _bufferSize = 30720;
	int _fd;

	std::string buildResponse() const;
};