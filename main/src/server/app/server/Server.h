#pragma once

#include <map>
#include "config/ServerConfig.h"
#include "config/MediaConfig.h"
#include "server/core/messages/Request.h"
#include "server/core/messages/Response.h"
#include "server/core/socketControllers/ServerSocketController.h"
#include "server/app/requestProcessors/RequestProcessor.h"
#include "server/app/project/Project.h"
#include "server/app/locationProcessor/LocationProcessor.h"
#include "server/app/cgi/CGIExecutor.h"
#include "utils/templates/Optional.h"

namespace webserv
{
	class Server;
}

std::ostream& operator<<(std::ostream& stream, const webserv::Server& server);

class webserv::Server : public IServerSocketListener
{
	friend std::ostream&::operator<<(std::ostream& stream, const Server& server);

public:

	Server(const config::ServerConfig& config, const config::MediaConfig& mediaConfig);
	~Server();

private:

	WebAddress _address;
	Project _project;
	LocationProcessor _locationProcessor;
	CGIExecutor _cgi;
	std::map<RequestMethod, RequestProcessor*> _requestProcessors;

	Server(Server&);
	Server& operator=(Server&);

	virtual Optional<Response> onServerReceivedRequest(const Request& request);
	bool processRedirect(const Location& location, Response& response);
	void processRequest(const Request& request, const std::string& localPath, Response& response);
};