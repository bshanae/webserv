#pragma once

#include <map>
#include "config/VirtualServerConfig.h"
#include "config/MediaConfig.h"
#include "server/core/messages/Request.h"
#include "server/core/messages/Response.h"
#include "server/core/socketControllers/ServerSocketController.h"
#include "server/app/requestProcessors/RequestProcessor.h"
#include "server/app/project/Project.h"
#include "server/app/cgi/CGIExecutor.h"
#include "utils/templates/Optional.h"

namespace webserv
{
	class VirtualServer;
}

std::ostream& operator<<(std::ostream& stream, const webserv::VirtualServer& server);

class webserv::VirtualServer : public IServerSocketListener
{
	friend std::ostream& ::operator<<(std::ostream& stream, const VirtualServer& server);

public:

	VirtualServer(const config::VirtualServerConfig& config, const config::MediaConfig& mediaConfig);
	~VirtualServer();

private:

	WebAddress _address;
	Project _project;
	CGIExecutor _cgi;
	std::map<RequestMethod, RequestProcessor*> _requestProcessors;

	VirtualServer(VirtualServer &);
	VirtualServer& operator=(VirtualServer &);

	virtual Optional<Response> onServerReceivedRequest(const Request& request);
	void processRegularRequest(const Request& request, Response& response);
	bool processCGIRequest(const Request& request, Response& response);
};