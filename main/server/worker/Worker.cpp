#include "Worker.h"

#include <cstdio>
#include <unistd.h>
#include <cerrno>
#include <string>
#include <sstream>
#include <iostream>
#include "server/request/Request.h"
#include "server/response/Response.h"

Worker::Worker(VirtualServer& context, int fd) : _context(context), _fd(fd)
{
}

Worker::Worker(const Worker& that) : _context(that._context), _fd(that._fd)
{

}

Worker& Worker::operator=(const Worker& that)
{
	this->_context = that._context;
	this->_fd = that._fd;

	return *this;
}

bool Worker::hasConnection() const
{
	return _fd != -1;
}

void Worker::processRequest()
{
	char requestStr[_bufferSize] = { 0 }; // TODO Optimize
	ssize_t bytesReceived = read(_fd, requestStr, _bufferSize);
	if (bytesReceived == -1)
	{
		if (errno == ECONNRESET)
		{
			close(_fd);
			_fd = -1;
		}

		// TODO ERROR
	}

	std::cout << "/// REQUEST" << std::endl;
	std::cout << requestStr;
	std::cout << "\\\\\\ REQUEST" << std::endl;

	Request request = Request::parse(requestStr);

	Response response;
	response.addHeader();
	response.addBody("Helloyjj word");

	const std::string responseStr = response.build();

	std::cout << "/// RESPONSE" << std::endl;
	std::cout << responseStr;
	std::cout << "\\\\\\ RESPONSE" << std::endl;

	const long bytesSent = write(_fd, responseStr.c_str(), responseStr.size());
	if (bytesSent != responseStr.size())
	{
		// TODO Error
	}
}