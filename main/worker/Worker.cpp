#include "Worker.h"
#include <cstdio>
#include <unistd.h>
#include <cerrno>
#include <string>
#include <sstream>

Worker::Worker(int fd) : _fd(fd)
{
}

bool Worker::hasConnection() const
{
	return _fd != -1;
}

void Worker::processRequest()
{
	char buffer[_bufferSize] = { 0 }; // TODO Optimize
	ssize_t bytesReceived = read(_fd, buffer, _bufferSize);
	if (bytesReceived == -1)
	{
		if (errno == ECONNRESET)
		{
			close(_fd);
			_fd = -1;
		}

		// TODO ERROR
	}

	const std::string response = buildResponse();

	const long bytesSent = write(_fd, response.c_str(), response.size());
	if (bytesSent != response.size())
	{
		// TODO Error
	}
}

std::string Worker::buildResponse() const
{
	std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";

	std::ostringstream ss;
	ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: "
	   << htmlFile.size()
	   << "\n\n"
	   << htmlFile;

	return ss.str();
}