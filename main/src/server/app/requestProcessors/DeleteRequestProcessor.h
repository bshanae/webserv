#pragma once

#include "config/MediaConfig.h"
#include "RequestProcessor.h"

namespace webserv
{
	class DeleteRequestProcessor;
}

class webserv::DeleteRequestProcessor : public RequestProcessor
{
public:

	DeleteRequestProcessor(Project& project, CGIExecutor& cgi);
	~DeleteRequestProcessor();

	virtual void processRequest(const Request& request, const config::LocationConfig& location, Response& response);
};
