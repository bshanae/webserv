#include "Worker.h"

#include <cstdio>
#include <unistd.h>
#include <cerrno>
#include "../messages/aux/StatusCode.h"
#include "tools/log/log.h"
#include "tools/exceptions/FileNotFoundException.h"

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

void Worker::onRequestReceived()
{
	Request request = readRequest();

	Response response;
	processRequest(request, response);

	writeResponse(response);
}

std::ostream& operator<<(std::ostream& stream, const Worker& worker)
{
	stream << "Worker(fd=" << worker._fd << ")";
	return stream;
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
	response.setDate(std::time(0));
	response.setServer("Webserv 21");

	const RequestMethod method = request.getMethod();
	if (method == RequestMethodGET)
	{
		try
		{
			const std::string file = _context.getProject().readFile(request.getUrl());

			response.setStatusCode(StatusCodeOk);
			response.setBody(MediaTypeHtml, file);
		}
		catch (const FileNotFoundException& exception)
		{
			response.setStatusCode(StatusCodeNotFound);
		}
		catch (const std::exception& exception)
		{
			// TODO
		}
	}
	else
	{
		log::e << log::entity << *this << log::endl
			   << "Unknown request method: " << request.getMethod() << log::endm;
	}
}

void Worker::logRequest(const std::string& str) const
{
	log::i << log::entity << *this << log::endl
		   << "Request:" << log::endl
		   << str << log::endl
		   << "@" << log::endm;
}

void Worker::logResponse(const std::string& str) const
{
	log::i << log::entity << *this << log::endl
		   << "Response:" << log::endl
		   << str << log::endl
		   << "@" << log::endm;
}