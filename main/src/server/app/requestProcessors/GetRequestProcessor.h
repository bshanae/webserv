#pragma once

#include "RequestProcessor.h"

class GetRequestProcessor : public RequestProcessor
{
public:

	GetRequestProcessor(Project& project, bool autoindex);

	virtual void processRequest(const Request& request, Response& response);

private:

	bool _autoindex;
};
