#include "Server.h"

#include "utils/algo/container.h"
#include "utils/sys/sys.path.h"
#include "common/exceptions/WebException.h"
#include "log/log.h"
#include "server/app/requestProcessors/GetRequestProcessor.h"
#include "server/app/requestProcessors/HeadRequestProcessor.h"
#include "server/app/requestProcessors/PostRequestProcessor.h"
#include "server/app/requestProcessors/PutRequestProcessor.h"
#include "server/app/requestProcessors/DeleteRequestProcessor.h"

using namespace webserv;
using namespace webserv::config;

Server::Server(const std::string& startDir, const ServerConfig& config, const MediaConfig& mediaConfig):
	_startDir(startDir),
	_name(config.name()),
	_address(config.address()),
	_project(config.root()),
	_locationProcessor(config.locations()),
	_cgi(config)
{
	_requestProcessors[RequestMethodGET] = new GetRequestProcessor(_project, _cgi, mediaConfig);
	_requestProcessors[RequestMethodHEAD] = new HeadRequestProcessor(_project, _cgi, mediaConfig);
	_requestProcessors[RequestMethodPOST] = new PostRequestProcessor(_project, _cgi);
	_requestProcessors[RequestMethodPUT] = new PutRequestProcessor(_project, _cgi);
	_requestProcessors[RequestMethodDELETE] = new DeleteRequestProcessor(_project, _cgi);
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

Response Server::respondToRequest(const Optional<Request>& request)
{
	Response response;
	response.setDate(std::time(0));
	response.setServer("Webserv 21");

	try
	{
		if (!request)
			throw WebException(StatusCodeBadRequest);

		const LocationConfig& location = _locationProcessor.resolveLocation(request->path());
		log::v << *this << log::startm << "Resolved location: " << location.remotePath() << log::endm;

		if (request->body().size() > location.maxClientBodySize().valueOr(SIZE_T_MAX))
			throw WebException(StatusCodePayloadTooLarge);

		validateRequest(*request, location);

		if (!processRedirect(location, response))
			processRequest(*request, location, response);

		return response;
	}
	catch (WebException& e)
	{
		log::e << *this << log::startm << "Web error. Code: " << e.code() << ". Cause: " << e.what() << log::endm;

		response.setStatusCode(e.code());
	}
	catch (std::exception& e)
	{
		log::e << *this << log::startm << "Unknown error: " << e.what() << log::endm;

		response.setStatusCode(StatusCodeInternalServerError);
	}

	if (response.needsBody())
		response.setBody(MediaType::Html, loadDefaultBody(response.getStatusCode()));

	return response;
}

void Server::validateRequest(const Request& request, const config::LocationConfig& location) const
{
	if (location.extensions() && !algo::contains(*location.extensions(), sys::path::extension(request.path())))
		throw WebException(StatusCodeNotFound);
	if (!algo::contains(location.methods(), request.method()))
		throw WebException(StatusCodeMethodNowAllowed);
}

bool Server::processRedirect(const LocationConfig& location, Response& response)
{
	if (location.redirectionUrl().empty())
		return false;

	response.setStatusCode((StatusCode)location.redirectionCode());
	response.setLocation(location.redirectionUrl());

	return true;
}

void Server::processRequest(const Request& request, const LocationConfig& location, Response& response)
{
	std::map<RequestMethod, RequestProcessor*>::iterator i = _requestProcessors.find(request.method());
	if (i == _requestProcessors.end())
		throw WebException(StatusCodeBadRequest, "Unsupported request method");

	i->second->processRequest(request, location, response);
}

std::string Server::loadDefaultBody(StatusCode code)
{
	const std::string defaultPageDir = sys::path::concat(_startDir, "main/res/default-pages/");
	const std::string defaultPage = sys::path::concat(defaultPageDir, std::to_string(code) + ".html");

	if (!sys::isFile(defaultPage))
		return "";

	return sys::readFile(defaultPage);
}

std::ostream& operator<<(std::ostream& stream, const Server& server)
{
	stream << "[Server:address=" << server._address << "]";
	return stream;
}