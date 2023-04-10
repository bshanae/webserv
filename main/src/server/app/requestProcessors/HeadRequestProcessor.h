#pragma once

#include "GetRequestProcessor.h"

namespace webserv
{
	class HeadRequestProcessor;
}

class webserv::HeadRequestProcessor : public GetRequestProcessor
{
public:

	HeadRequestProcessor(Project& project, CGIExecutor& cgi, bool autoindex, const config::MediaConfig& mediaConfig);
	virtual ~HeadRequestProcessor();

	virtual void processRequest(const Request& request, const std::string& localPath, Response& response);
};
