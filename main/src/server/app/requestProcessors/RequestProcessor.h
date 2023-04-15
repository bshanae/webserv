#pragma once

#include "config/LocationConfig.h"
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

	virtual void processRequest(const Request& request, const config::LocationConfig& location, Response& response) = 0;

protected:

	Project& project();
	std::string resolveRemotePath(const Request& request);
	std::string resolveLocalPath(const Request& request, const config::LocationConfig& location);
	std::string resolveFullLocalPath(const Request& request, const config::LocationConfig& location);
	bool tryExecuteCGI(const Request& request,  const config::LocationConfig& location, Response& response);

private:

	Project& _project;
	CGIExecutor& _cgi;
};