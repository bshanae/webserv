#include "HeadRequestProcessor.h"

using namespace webserv;
using namespace webserv::config;

HeadRequestProcessor::HeadRequestProcessor(Project& project, CGIExecutor& cgi, bool autoindex, const MediaConfig& mediaConfig):
	GetRequestProcessor(project, cgi, autoindex, mediaConfig)
{
}

HeadRequestProcessor::~HeadRequestProcessor()
{}

void HeadRequestProcessor::processRequest(const Request& request, const std::string& localPath, Response& response)
{
	GetRequestProcessor::processRequest(request, localPath, response);
	response.ignoreBody();
}