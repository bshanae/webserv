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

	GetRequestProcessor(Project& project, CGIExecutor& cgi, bool autoindex, const config::MediaConfig& mediaConfig);
	virtual ~GetRequestProcessor();

	virtual void processRequest(const Request& request, const std::string& localPath, Response& response);

private:

	bool _autoindex;
	const config::MediaConfig _mediaConfig;
};
