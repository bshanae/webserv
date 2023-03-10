#pragma once

#include "RequestProcessor.h"

class GetRequestProcessor : public RequestProcessor
{
public :

	explicit GetRequestProcessor(Project& project);

	virtual void processRequest(const Request& request, Response& response);
};
