#include "Server.h"

#include "log/log.h"
#include "server/app/requestProcessors/GetRequestProcessor.h"
#include "common/exceptions/WebException.h"

using namespace webserv;
using namespace webserv::config;

Server::Server(const ServerConfig& config, const MediaConfig& mediaConfig):
	_project(config.root()),
	_address(config.address()),
	_cgi(config.cgi(), config, _project)
{
	_requestProcessors[RequestMethodGET] = new GetRequestProcessor(_project, config.autoindex(), mediaConfig);
}

Server::~Server()
{
	for (std::map<RequestMethod, RequestProcessor*>::iterator i = _requestProcessors.begin(); i != _requestProcessors.end(); i++)
		delete i->second;
}

Optional<Response> Server::onServerReceivedRequest(const Request& request)
{
	// TODO Check server name

	Response response;
	response.setDate(std::time(0));
	response.setServer("Webserv 21");

	try
	{
		if (processCGIRequest(request, response))
			return response;

		processRegularRequest(request, response);
	}
	catch (WebException& e)
	{
		log::e << *this << log::startm << "Web error. Code: " << e.code() << ". Cause: " << e.what() << log::endm;

		response.setStatusCode(e.code());
		response.setEmptyBody();
	}
	catch (std::exception& e)
	{
		log::e << *this << log::startm << "Unknown error: " << e.what() << log::endm;

		response.setStatusCode(StatusCodeInternalServerError);
		response.setEmptyBody();
	}

	return response;
}

void Server::processRegularRequest(const Request& request, Response& response)
{
	std::map<RequestMethod, RequestProcessor*>::iterator i = _requestProcessors.find(request.method());
	if (i == _requestProcessors.end())
		throw WebException(StatusCodeBadRequest, "Unsupported request method");

	i->second->processRequest(request, response);
}

bool Server::processCGIRequest(const Request& request, Response& response)
{
	const std::string& remotePath = request.path();
	const std::string& localPath = _project.resolvePath(request.path());

	if (!_cgi.isCGI(remotePath, localPath))
		return false;

	if (!sys::isFile(localPath))
		throw WebException(StatusCodeNotFound, "CGI script not found.");

	CGIOutput output = _cgi.executeCGI(request);

	response.setStatusCode(StatusCodeOk);
	response.setBody(output.body);
	for (int i = 0; i < output.headers.size(); i++)
		response.addHeader(output.headers[i]);

	return true;
}

std::ostream& operator<<(std::ostream& stream, const Server& server)
{
	stream << "[Server:address=" << server._address << "]";
	return stream;
}