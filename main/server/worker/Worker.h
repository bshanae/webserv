#pragma once

#include <cstddef>
#include <string>
#include "context/Context.h"
#include "../cgi/CGIExecutor.h"
#include "../messages/request/Request.h"
#include "../messages/response/Response.h"

class Worker
{
public:

	Worker(Context& context, int fd);
	Worker(const Worker& that);
	Worker& operator=(const Worker& that);

	bool hasConnection() const;
	void onRequestReceived();

	friend std::ostream& operator<<(std::ostream& stream, const Worker& worker);

private:

	static const size_t bufferSize = 30720;

	Context& _context;
	CGIExecutor _cgiExecutor;
	int _fd;

	Request readRequest();
	void writeResponse(const Response& response);
	void processRequest(const Request& request, Response& response);

	void logRequest(const std::string& str) const;
	void logResponse(const std::string& str) const;
};

std::ostream& operator<<(std::ostream& stream, const Worker& worker);