#include "PutRequestProcessor.h"

#include <fstream>
#include "common/exceptions/WebException.h"
#include "server/app/project/IndexGenerator.h"
#include "utils/sys/sys.h"

using namespace webserv;
using namespace webserv::config;

PutRequestProcessor::PutRequestProcessor(Project& project, CGIExecutor& cgi) : RequestProcessor(project, cgi)
{
}

PutRequestProcessor::~PutRequestProcessor()
{
}

void PutRequestProcessor::processRequest(const Request& request, const config::LocationConfig& location, Response& response)
{
	if (tryExecuteCGI(request, location, response))
		return;

	const std::string& fullLocalPath = resolveFullLocalPath(request, location);

	if (sys::isFile(fullLocalPath))
	{
		std::ofstream fstream(fullLocalPath);
		if (!fstream)
			throw WebException(StatusCodeForbidden);

		fstream << request.body();
		response.setStatusCode(StatusCodeNoContent);
	}
	else
	{
		std::ofstream fstream(fullLocalPath, std::ofstream::out | std::ofstream::trunc);
		if (!fstream)
			throw WebException(StatusCodeForbidden);

		fstream << request.body();
		response.setStatusCode(StatusCodeCreated);
	}
}