#pragma once

#include "config/MediaConfig.h"
#include "RequestProcessor.h"

namespace webserv
{
	class PutRequestProcessor;
}

class webserv::PutRequestProcessor : public RequestProcessor
{
public:

	PutRequestProcessor(Project& project, CGIExecutor& cgi);
	~PutRequestProcessor();

	virtual void processRequest(const Request& request, const config::LocationConfig& location, Response& response);

private:
};