#include "VirtualServer.h"

#include "server/app/project/IndexGenerator.h"
#include "log/log.h"
#include "utils/sys/sys.path.h"
#include "utils/exceptions/FileException.h"

VirtualServer::VirtualServer(const VirtualServerConfig& config) :
	_project(config.root()),
	_address(config.address()),
	_cgi(config.cgi(), config, _project)
{

}

const WebAddress& VirtualServer::address() const
{
	return _address;
}

Optional<Response> VirtualServer::onServerReceivedRequest(const Request& request)
{
	Response response;
	response.setDate(std::time(0));
	response.setServer("Webserv 21");

	const RequestMethod method = request.method();
	const std::string& remotePath = request.path();
	const std::string& localPath = _project.resolvePath(request.path());

	if (_cgi.isCGI(remotePath, localPath))
	{
		try
		{
			CGIOutput output = _cgi.executeCGI(request);

			response.setStatusCode(StatusCodeOk);
			response.setBody(output.body);
			for (int i = 0; i < output.headers.size(); i++)
				response.addHeader(output.headers[i]);

			return response;
		}
		catch (std::exception& e)
		{
			// TODO
			return Optional<Response>();
		}
	}

	if (method == RequestMethodGET)
	{
		try
		{
			if (sys::isDirectory(localPath))
			{
				// TODO Check indexing in config
				response.setStatusCode(StatusCodeOk);
				response.setBody(MediaType::Html, IndexGenerator::generatePage(_project, remotePath, localPath));
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
		catch (const FileException& exception)
		{
			response.setStatusCode(StatusCodeNotFound);
			response.setEmptyBody();
		}
		catch (const std::exception& exception)
		{
			// TODO
		}
	}
	else
	{
		log::e << *this << log::startm << "Unknown request method: " << request.method() << log::endm;
	}

	return response;
}

std::ostream& operator<<(std::ostream& stream, const VirtualServer& server)
{
	stream << "[VirtualServer:address=" << server._address << "]";
	return stream;
}