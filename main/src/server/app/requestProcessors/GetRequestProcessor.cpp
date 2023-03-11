#include "GetRequestProcessor.h"

#include "common/exceptions/WebException.h"
#include "server/app/project/IndexGenerator.h"
#include "utils/sys/sys.h"
#include "utils/sys/sys.path.h"

GetRequestProcessor::GetRequestProcessor(Project& project, bool autoindex): RequestProcessor(project), _autoindex(autoindex)
{
}

void GetRequestProcessor::processRequest(const Request& request, Response& response)
{
	const std::string& remotePath = request.path();
	const std::string& localPath = project().resolvePath(request.path());

	if (sys::isDirectory(localPath))
	{
		const std::string indexPath = sys::path::concat(localPath, "index.html");
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
			response.setBody(MediaType::Html, IndexGenerator::generatePage(project(), remotePath, localPath));
		}
	}
	else
	{
		response.setStatusCode(StatusCodeOk);
		response.setBody(
			MediaType::fromFileExtension(sys::path::extension(localPath)),
			sys::readFile(localPath)
		);
	}
}