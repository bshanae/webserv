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

	GetRequestProcessor(Project& project, bool autoindex, const config::MediaConfig& mediaConfig);

	virtual void processRequest(const Request& request, Response& response);

private:

	bool _autoindex;
	const config::MediaConfig _mediaConfig;
};
