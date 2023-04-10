#include "PostRequestProcessor.h"

#include "utils/sys/sys.path.h"
#include "common/exceptions/WebException.h"
#include "server/app/project/IndexGenerator.h"

using namespace webserv;
using namespace webserv::config;

PostRequestProcessor::PostRequestProcessor(Project& project, CGIExecutor& cgi): RequestProcessor(project, cgi)
{
}

PostRequestProcessor::~PostRequestProcessor()
{}

void PostRequestProcessor::processRequest(const Request& request, const std::string& localPath, Response& response)
{
	if (tryProcessCGI(request, localPath, response))
		return;
}