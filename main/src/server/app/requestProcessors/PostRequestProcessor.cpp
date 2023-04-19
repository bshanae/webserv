#include "PostRequestProcessor.h"

#include "common/exceptions/WebException.h"
#include "server/app/project/IndexGenerator.h"

using namespace webserv;
using namespace webserv::config;

PostRequestProcessor::PostRequestProcessor(Project& project, CGIExecutor& cgi): RequestProcessor(project, cgi)
{
}

PostRequestProcessor::~PostRequestProcessor()
{}

void PostRequestProcessor::processRequest(const Request& request, const LocationConfig& location, Response& response)
{
	if (tryExecuteCGI(request, location, response))
		return;

	response.setStatusCode(StatusCodeNoContent);
}