#pragma once

#include <map>
#include <vector>
#include "config/ServerConfig.h"
#include "config/MediaConfig.h"
#include "server/core/messages/Request.h"
#include "server/core/messages/Response.h"
#include "server/core/socketControllers/server/ServerSocketController.h"
#include "server/app/requestProcessors/RequestProcessor.h"
#include "server/app/project/Project.h"
#include "server/app/LocationProcessor.h"
#include "server/app/cgi/CGIExecutor.h"
#include "utils/templates/Optional.h"

namespace webserv
{
	class Server;
}

std::ostream& operator<<(std::ostream& stream, const webserv::Server& server);

class webserv::Server : public IServerSocketDelegate
{
	friend std::ostream&::operator<<(std::ostream& stream, const Server& server);

public:

	Server(const std::string& startDir, const config::ServerConfig& config, const config::MediaConfig& mediaConfig);
	virtual ~Server();

private:

	std::string _startDir;
	std::string _name;
	WebAddress _address;
	Project _project;
	LocationProcessor _locationProcessor;
	CGIExecutor _cgi;
	std::map<RequestMethod, RequestProcessor*> _requestProcessors;

	Server(Server&);
	Server& operator=(Server&);

	virtual bool targetOfRequest(const Request& request);
	virtual Response respondToRequest(const Optional<Request>& request);
	void validateRequest(const Request& request, const config::LocationConfig& location) const;
	bool processRedirect(const config::LocationConfig& location, Response& response);
	void processRequest(const Request& request, const config::LocationConfig& location, Response& response);
	std::string loadDefaultBody(StatusCode code);
};