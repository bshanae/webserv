#include "SocketController.h"

#include <ostream>
#include <sys/fcntl.h>
#include "utils/exceptions/InvalidOperationException.h"

using namespace webserv;

SocketController::SocketController() : _socket(sys::nullFd), _newSocketControllerListener(NULL)
{
}

SocketController::~SocketController()
{
	sys::close(_socket);
}

sys::FDescriptor SocketController::socket() const
{
	return _socket;
}

void SocketController::setSocketCreationControllerListener(ISocketControllerCreationListener* listener)
{
	_newSocketControllerListener = listener;
}

void SocketController::bindSocket(sys::FDescriptor socket)
{
	if (_socket != sys::nullFd)
		throw InvalidOperationException("Socket is already bound!");

	_socket = socket;
}

void SocketController::unbindSocket()
{
	sys::close(_socket);
}

void SocketController::notifyAboutNewController(SocketController *newController)
{
	if (_newSocketControllerListener != NULL)
		_newSocketControllerListener->onSocketControllerCreated(newController);
}

std::ostream& operator<<(std::ostream& stream, const SocketController& controller)
{
	stream << "[SocketController:socket=" << controller.socket() << "]";
	return stream;
}