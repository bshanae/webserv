#include "Worker.h"

#include <cstdio>
#include <unistd.h>
#include <cerrno>
#include <string>
#include "server/response/Response.h"
#include "tools/log/log.h"

Worker::Worker(Context& context, int fd) : _context(context), _fd(fd)
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

void Worker::onDataReceived()
{
	Request request = readRequest();

	Response response;
	processRequest(request, response);

	writeResponse(response);
}

Request Worker::readRequest()
{
	char requestStr[bufferSize] = { 0 }; // TODO Optimize
	ssize_t bytesReceived = read(_fd, requestStr, bufferSize);
	if (bytesReceived == -1)
	{
		if (errno == ECONNRESET)
		{
			close(_fd);
			_fd = -1;
		}

		// TODO ERROR
	}

	logRequest(requestStr);
	return Request::parse(requestStr);
}

void Worker::writeResponse(const Response& response)
{
	const std::string responseStr = response.build();
	logResponse(responseStr);

	const long bytesSent = write(_fd, responseStr.c_str(), responseStr.size());
	if (bytesSent != responseStr.size())
	{
		// TODO Error
	}
}

void Worker::processRequest(const Request& request, Response& response)
{
	const Request::Method method = request.getMethod();
	if (method == Request::GET)
	{
		response.addHeader();
		response.addBody(_context.getProject().readFile(request.getUrl()));
	}
	else
	{
		log::e << log::entity << "Worker(fd=" << _fd << ")" << log::endl
			   << "Unknown request method: " << request.getMethod() << log::endm;
	}
}

void Worker::logRequest(const std::string& str) const
{
	log::i << log::entity << "Worker(fd=" << _fd << ")" << log::endl
		   << "Request:" << log::endl
		   << str << log::endl
		   << "@" << log::endm;
}

void Worker::logResponse(const std::string& str) const
{
	log::i << log::entity << "Worker(fd=" << _fd << ")" << log::endl
		   << "Response:" << log::endl
		   << str << log::endl
		   << "@" << log::endm;
}