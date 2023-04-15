#pragma once

#include "config/MediaConfig.h"
#include "RequestProcessor.h"

namespace webserv
{
	class PostRequestProcessor;
}

class webserv::PostRequestProcessor : public RequestProcessor
{
public:

	PostRequestProcessor(Project& project, CGIExecutor& cgi);
	~PostRequestProcessor();

	virtual void processRequest(const Request& request, const config::LocationConfig& location, Response& response);

private:
};
