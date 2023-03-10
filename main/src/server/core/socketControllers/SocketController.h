#pragma once

#include <iosfwd>
#include "utils/sys/sys.h"

class SocketController;

class ISocketControllerCreationListener
{
public:

	virtual void onSocketControllerCreated(SocketController *newController) = 0;
};

class SocketController
{
public:

	SocketController();
	virtual ~SocketController();

	sys::FDescriptor socket() const;

	virtual void processSocketEvent() = 0;
	void setSocketCreationControllerListener(ISocketControllerCreationListener* listener);

protected:

	void bindSocket(sys::FDescriptor socket);
	void unbindSocket();
	void notifyAboutNewController(SocketController *newController);

private:

	sys::FDescriptor _socket;
	ISocketControllerCreationListener *_newSocketControllerListener;
};

std::ostream& operator<<(std::ostream& stream, const SocketController& controller);