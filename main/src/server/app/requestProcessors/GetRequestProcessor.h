#pragma once

#include "config/MediaConfig.h"
#include "RequestProcessor.h"

namespace webserv
{
	class GetRequestProcessor;
}

class webserv::GetRequestProcessor : public RequestProcessor
{
public:

	GetRequestProcessor(Project& project, CGIExecutor& cgi, const config::MediaConfig& mediaConfig);
	virtual ~GetRequestProcessor();

	virtual void processRequest(const Request& request, const Location& location, Response& response);

private:

	const config::MediaConfig _mediaConfig;
};
