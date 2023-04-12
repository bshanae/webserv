#include "GetRequestProcessor.h"

#include "utils/sys/sys.h"
#include "utils/sys/sys.path.h"
#include "log/log.h"
#include "common/exceptions/WebException.h"
#include "server/app/project/IndexGenerator.h"

using namespace webserv;
using namespace webserv::config;

GetRequestProcessor::GetRequestProcessor(Project& project, CGIExecutor& cgi, const MediaConfig& mediaConfig):
	RequestProcessor(project, cgi),
	_mediaConfig(mediaConfig)
{
}

GetRequestProcessor::~GetRequestProcessor()
{}

void GetRequestProcessor::processRequest(const Request& request, const Location& location, Response& response)
{
	const std::string& remotePath = request.path();
	const std::string localPath = location.transformRemotePath(request.path());
	const std::string& fullLocalPath = project().resolvePath(localPath);

	if (tryProcessCGI(request, localPath, response))
		return;

	if (sys::isDirectory(fullLocalPath))
	{
		if (location.index())
		{
			const std::string indexPath = project().resolvePath(sys::path::concat(localPath, *location.index()));
			if (!sys::isFile(indexPath))
				throw WebException(StatusCodeNotFound, "Index not found: " + indexPath);

			response.setStatusCode(StatusCodeOk);
			response.setBody(MediaType::Html, sys::readFile(indexPath));
		}
		else
		{
			if (!location.autoindex())
				throw WebException(StatusCodeNotFound, "Directory is requested, but autoindex is disabled.");

			response.setStatusCode(StatusCodeOk);
			response.setBody(MediaType::Html, IndexGenerator::generatePage(project(), remotePath, fullLocalPath));
		}

		return;
	}
	else
	{
		MediaType mediaType = MediaType::Default;
		try
		{
			mediaType = _mediaConfig.fileExtensionToMediaType().at(sys::path::extension(localPath));
		}
		catch (...)
		{
			log::w << "[GetRequestProcessor]" << log::startm << "Unknown extension " << sys::path::extension(localPath) << log::endm;
		}

		if (!sys::isFile(fullLocalPath))
			throw WebException(StatusCodeNotFound, "File not found: " + fullLocalPath);

		response.setStatusCode(StatusCodeOk);
		response.setBody(mediaType, sys::readFile(fullLocalPath));
	}
}