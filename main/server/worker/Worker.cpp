#include "Worker.h"

#include <cstdio>
#include <unistd.h>
#include <cerrno>
#include "tools/IndexGenerator.h"
#include "tools/log/log.h"
#include "tools/exceptions/FileNotFoundException.h"
#include "tools/str/str.h"

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
	stream << "[Worker:fd=" << worker._fd << "]";
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
	const std::string &url = request.getUrl();

	if (method == RequestMethodGET)
	{
		try
		{
			if (_context.getProject().isDirectory(url))
			{
				// TODO Check indexing in config
				response.setStatusCode(StatusCodeOk);
				response.setBody(MediaTypeHtml, IndexGenerator::generatePage(_context.getProject(), url));
			}
			else
			{
				response.setStatusCode(StatusCodeOk);
				response.setBody(MediaTypeHtml, _context.getProject().readFile(url));
			}
		}
		catch (const FileNotFoundException& exception)
		{
			response.setStatusCode(StatusCodeNotFound);
			response.setEmptyBody();
		}
		catch (const std::exception& exception)
		{
			// TODO
		}
	}
	else
	{
		log::e << *this << log::startm << "Unknown request method: " << request.getMethod() << log::endm;
	}
}

void Worker::logRequest(const std::string& str) const
{
	std::string markedStr = str;
	markEmptyLines(markedStr, "\r\n");

	log::v << *this << log::startm << "REQUEST" << log::endl
		   << markedStr << log::endm;
}

void Worker::logResponse(const std::string& str) const
{
	if (!log::v.enabled)
		return;

	std::string markedStr = str;
	markEmptyLines(markedStr, "\r\n");

	log::v << *this << log::startm << "RESPONSE" << log::endl
		    << markedStr << log::endm;
}