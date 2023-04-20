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

std::string RequestProcessor::resolveRemotePath(const Request& request)
{
	return request.path();
}

std::string RequestProcessor::resolveLocalPath(const Request& request, const config::LocationConfig& location)
{
	return location.transformRemotePath(resolveRemotePath(request));
}

std::string RequestProcessor::resolveFullLocalPath(const Request& request, const config::LocationConfig& location)
{
	return project().resolvePath(resolveLocalPath(request, location));
}

bool RequestProcessor::tryExecuteCGI(const Request& request,  const config::LocationConfig& location, Response& response)
{
	if (!location.cgiEnabled())
		return false;

	const std::string localPath = location.cgiForward().valueOr(resolveLocalPath(request, location));
	const std::string fullLocalPath = project().resolvePath(localPath);

	if (!sys::isFile(fullLocalPath))
		throw WebException(StatusCodeNotFound, "CGI script not found.");

	CGIOutput output = _cgi.executeCGI(request, fullLocalPath);

	response.setStatusCode(StatusCodeOk);
	response.setBody(output.body);
	for (int i = 0; i < output.headers.size(); i++)
		response.addHeader(output.headers[i]);

	return true;
}

