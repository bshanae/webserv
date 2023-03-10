#include "GetRequestProcessor.h"

#include "server/app/project/IndexGenerator.h"
#include "utils/sys/sys.h"
#include "utils/sys/sys.path.h"

GetRequestProcessor::GetRequestProcessor(Project& project): RequestProcessor(project)
{
}

void GetRequestProcessor::processRequest(const Request& request, Response& response)
{
	const std::string& remotePath = request.path();
	const std::string& localPath = project().resolvePath(request.path());

	if (sys::isDirectory(localPath))
	{
		// TODO Check indexing in config
		response.setStatusCode(StatusCodeOk);
		response.setBody(MediaType::Html, IndexGenerator::generatePage(project(), remotePath, localPath));
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