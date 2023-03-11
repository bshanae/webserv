#pragma once

#include "config/MediaConfig.h"
#include "RequestProcessor.h"

class GetRequestProcessor : public RequestProcessor
{
public:

	GetRequestProcessor(Project& project, bool autoindex, const MediaConfig& mediaConfig);

	virtual void processRequest(const Request& request, Response& response);

private:

	bool _autoindex;
	const MediaConfig _mediaConfig;
};
