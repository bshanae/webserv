#include "DeleteRequestProcessor.h"

#include "utils/sys/sys.h"
#include "utils/sys/sys.path.h"
#include "common/exceptions/WebException.h"

using namespace webserv;
using namespace webserv::config;

DeleteRequestProcessor::DeleteRequestProcessor(Project& project, CGIExecutor& cgi): RequestProcessor(project, cgi)
{}

DeleteRequestProcessor::~DeleteRequestProcessor()
{}

void DeleteRequestProcessor::processRequest(const Request& request, const config::LocationConfig& location, Response& response)
{
	if (tryExecuteCGI(request, location, response))
		return;

	const std::string& fullLocalPath = resolveFullLocalPath(request, location);

	if (sys::isFile(fullLocalPath))
	{
		if (sys::remove(fullLocalPath))
			response.setStatusCode(StatusCodeNoContent);
		else
			response.setStatusCode(StatusCodeForbidden);
	}
	else
	{
		response.setStatusCode(StatusCodeNotFound);
	}
}