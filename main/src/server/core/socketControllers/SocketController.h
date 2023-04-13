#pragma once

#include <iosfwd>
#include "utils/sys/sys.h"
#include "server/core/SocketEvent.h"

namespace webserv
{
	class ISocketControllerCreationListener;
	class SocketController;
}

class webserv::ISocketControllerCreationListener
{
public:

	virtual void onSocketControllerCreated(SocketController *newController) = 0;
};

std::ostream& operator<<(std::ostream& stream, const webserv::SocketController& controller);

class webserv::SocketController
{
public:

	SocketController();
	virtual ~SocketController();

	sys::FDescriptor socket() const;

	virtual void processSocketEvent(SocketEvent event) = 0;
	void setSocketCreationControllerListener(ISocketControllerCreationListener* listener);

protected:

	void bindSocket(sys::FDescriptor socket);
	void unbindSocket();
	void notifyAboutNewController(SocketController *newController);

private:

	sys::FDescriptor _socket;
	ISocketControllerCreationListener *_newSocketControllerListener;
};