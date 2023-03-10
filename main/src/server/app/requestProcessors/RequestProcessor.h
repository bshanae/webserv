#pragma once

#include "server/core/messages/Request.h"
#include "server/core/messages/Response.h"
#include "server/app/project/Project.h"

class RequestProcessor
{
public:

	explicit RequestProcessor(Project& project);
	virtual ~RequestProcessor();

	virtual void processRequest(const Request& request, Response& response) = 0;

protected:

	Project& project();

private:

	Project& _project;
};