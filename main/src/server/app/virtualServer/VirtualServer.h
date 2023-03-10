#pragma once

#include "config/VirtualServerConfig.h"
#include "server/core/messages/Request.h"
#include "server/core/messages/Response.h"
#include "server/core/socketControllers/ServerSocketController.h"
#include "server/app/project/Project.h"
#include "server/app/cgi/CGIExecutor.h"
#include "utils/templates/Optional.h"

class VirtualServer : public IServerSocketListener
{
	friend std::ostream& operator<<(std::ostream& stream, const VirtualServer& server);

public:

	explicit VirtualServer(const VirtualServerConfig& config);

	const WebAddress& address() const;

private:

	WebAddress _address;
	Project _project;
	CGIExecutor _cgi;

	virtual Optional<Response> onServerReceivedRequest(const Request& request);
};

std::ostream& operator<<(std::ostream& stream, const VirtualServer& server);