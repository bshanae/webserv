#pragma once

#include "common/Location.h"
#include "server/core/messages/Request.h"
#include "server/core/messages/Response.h"
#include "server/app/project/Project.h"
#include "server/app/cgi/CGIExecutor.h"

namespace webserv
{
	class RequestProcessor;
};

class webserv::RequestProcessor
{
public:

	explicit RequestProcessor(Project& project, CGIExecutor& cgi);
	virtual ~RequestProcessor();

	virtual void processRequest(const Request& request, const Location& location, Response& response) = 0;

protected:

	Project& project();
	bool tryProcessCGI(const Request& request, const std::string& localPath, Response& response);

private:

	Project& _project;
	CGIExecutor& _cgi;
};