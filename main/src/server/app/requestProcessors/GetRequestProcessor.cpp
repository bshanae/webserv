#include "GetRequestProcessor.h"

#include "common/exceptions/WebException.h"
#include "server/app/project/IndexGenerator.h"
#include "utils/sys/sys.h"
#include "utils/sys/sys.path.h"

using namespace webserv;
using namespace webserv::config;

GetRequestProcessor::GetRequestProcessor(Project& project, CGIExecutor& cgi, bool autoindex, const MediaConfig& mediaConfig):
	RequestProcessor(project, cgi),
	_autoindex(autoindex),
	_mediaConfig(mediaConfig)
{
}

GetRequestProcessor::~GetRequestProcessor()
{}

void GetRequestProcessor::processRequest(const Request& request, const std::string& localPath, Response& response)
{
	if (tryProcessCGI(request, localPath, response))
		return;

	const std::string& remotePath = request.path();
	const std::string& fullLocalPath = project().resolvePath(localPath);

	if (sys::isDirectory(fullLocalPath))
	{
		const std::string indexPath = sys::path::concat(fullLocalPath, "index.html");
		if (sys::isFile(indexPath))
		{
			response.setStatusCode(StatusCodeOk);
			response.setBody(MediaType::Html, sys::readFile(indexPath));
		}
		else
		{
			if (!_autoindex)
				throw WebException(StatusCodeNotFound, "Directory is requested, but autoindex is disabled.");

			response.setStatusCode(StatusCodeOk);
			response.setBody(MediaType::Html, IndexGenerator::generatePage(project(), remotePath, fullLocalPath));
		}
	}
	else if (sys::isFile(fullLocalPath))
	{
		response.setStatusCode(StatusCodeOk);
		response.setBody(
			_mediaConfig.fileExtensionToMediaType().at(sys::path::extension(fullLocalPath)),
			sys::readFile(fullLocalPath)
		);
	}
	else
	{
		throw WebException(StatusCodeNotFound, "File not found: " + fullLocalPath);
	}
}