#pragma once

#include <sys/poll.h>
#include <vector>
#include "utils/sys/sys.h"
#include "server/core/socketControllers/SocketController.h"

class CoreServer : public ISocketControllerCreationListener
{
public:

	void registerSocketController(SocketController* controller);
	void run();

private:

	std::vector<pollfd> _pollingTargets;
	std::vector<SocketController*> _socketControllers;
	std::vector<SocketController*> _newSocketControllers;

	virtual void onSocketControllerCreated(SocketController *newController);
};

std::ostream& operator<<(std::ostream& stream, const CoreServer& _);