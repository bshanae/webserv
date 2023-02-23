#include "Response.h"

void Response::addHeader()
{
	_buffer << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
}

void Response::addBody(const std::string& data)
{
	_buffer << data.size()
			<< "\n\n"
			<< data;
}

std::string Response::build() const
{
	// TODO Maybe optimize this
	return _buffer.str();
}