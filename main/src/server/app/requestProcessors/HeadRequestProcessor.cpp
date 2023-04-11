#include "HeadRequestProcessor.h"

using namespace webserv;
using namespace webserv::config;

HeadRequestProcessor::HeadRequestProcessor(Project& project, CGIExecutor& cgi, const MediaConfig& mediaConfig):
	GetRequestProcessor(project, cgi, mediaConfig)
{
}

HeadRequestProcessor::~HeadRequestProcessor()
{}

void HeadRequestProcessor::processRequest(const Request& request, const Location& location, Response& response)
{
	GetRequestProcessor::processRequest(request, location, response);
	response.ignoreBody();
}