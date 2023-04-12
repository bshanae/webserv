#include "Server.h"

#include "utils/algo/container.h"
#include "common/exceptions/WebException.h"
#include "log/log.h"
#include "server/app/requestProcessors/GetRequestProcessor.h"
#include "server/app/requestProcessors/HeadRequestProcessor.h"
#include "server/app/requestProcessors/PostRequestProcessor.h"

using namespace webserv;
using namespace webserv::config;

Server::Server(const ServerConfig& config, const MediaConfig& mediaConfig):
	_name(config.name()),
	_address(config.address()),
	_project(config.root()),
	_locationProcessor(config.locations()),
	_cgi(config.cgi(), config, _project)
{
	_requestProcessors[RequestMethodGET] = new GetRequestProcessor(_project, _cgi, mediaConfig);
	_requestProcessors[RequestMethodHEAD] = new HeadRequestProcessor(_project, _cgi, mediaConfig);
	_requestProcessors[RequestMethodPOST] = new PostRequestProcessor(_project, _cgi);
}

Server::~Server()
{
	for (std::map<RequestMethod, RequestProcessor*>::iterator i = _requestProcessors.begin(); i != _requestProcessors.end(); i++)
		delete i->second;
}

bool Server::targetOfRequest(const Request& request)
{
	Optional<std::string> hostName = request.hostName();
	if (!hostName)
		return false;

	return *hostName == _name;
}

Response Server::respondToRequest(const Request& request)
{
	Response response;
	response.setDate(std::time(0));
	response.setServer("Webserv 21");

	try
	{
		const Location& location = _locationProcessor.resolveLocation(request.path());
		if (!algo::contains(location.methods(), request.method()))
			throw WebException(StatusCodeMethodNowAllowed);

		if (processRedirect(location, response))
			return response;
		processRequest(request, location, response);
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

bool Server::processRedirect(const Location& location, Response& response)
{
	if (location.redirectionUrl().empty())
		return false;

	response.setStatusCode(location.redirectionCode());
	response.setLocation(location.redirectionUrl());
	response.setEmptyBody();

	return true;
}

void Server::processRequest(const Request& request, const Location& location, Response& response)
{
	std::map<RequestMethod, RequestProcessor*>::iterator i = _requestProcessors.find(request.method());
	if (i == _requestProcessors.end())
		throw WebException(StatusCodeBadRequest, "Unsupported request method");

	i->second->processRequest(request, location, response);
}

std::ostream& operator<<(std::ostream& stream, const Server& server)
{
	stream << "[Server:address=" << server._address << "]";
	return stream;
}