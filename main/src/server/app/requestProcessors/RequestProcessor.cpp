#include "RequestProcessor.h"

#include "utils/sys/sys.h"
#include "common/exceptions/WebException.h"

using namespace webserv;

RequestProcessor::RequestProcessor(Project& project, CGIExecutor& cgi) : _project(project), _cgi(cgi)
{
}

RequestProcessor::~RequestProcessor()
{
}

Project& RequestProcessor::project()
{
	return _project;
}

bool RequestProcessor::tryProcessCGI(const Request& request, const std::string& localPath, Response& response)
{
	const std::string& remotePath = request.path();
	const std::string& fullLocalPath = _project.resolvePath(localPath);

	if (!_cgi.isCGI(remotePath, fullLocalPath))
		return false;

	if (!sys::isFile(fullLocalPath))
		throw WebException(StatusCodeNotFound, "CGI script not found.");

	CGIOutput output = _cgi.executeCGI(request);

	response.setStatusCode(StatusCodeOk);
	response.setBody(output.body);
	for (int i = 0; i < output.headers.size(); i++)
		response.addHeader(output.headers[i]);

	return true;
}

