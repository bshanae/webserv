#include "CoreServer.h"

#include "log/log.h"

using namespace webserv;

void CoreServer::registerSocketController(SocketController* controller)
{
	log::i << *this << log::startm << "Register " << *controller << log::endm;

	controller->setSocketCreationControllerListener(this);

	_socketControllers.push_back(controller);
	_pollingTargets.push_back((pollfd){ .fd = controller->socket(), .events = POLLRDNORM });
}

void CoreServer::run()
{
	log::i << *this << log::startm << "Run." << log::endm;

	while (!sys::TerminationRequested)
	{
		int readyCount = poll(_pollingTargets.data(), _pollingTargets.size(), 0);
		// TODO Check error
		if (readyCount == 0)
			continue;

		for (int i = 0; i < _pollingTargets.size() && readyCount > 0; i++)
		{
			if (!(_pollingTargets[i].revents & (POLLRDNORM | POLLERR)))
				continue;

			_socketControllers[i]->processSocketEvent();

			if (_socketControllers[i]->socket() == sys::nullFd)
			{
				log::i << *this << log::startm << "Unregister " << *_socketControllers[i] << log::endm;

				_pollingTargets.erase(_pollingTargets.begin() + i);
				_socketControllers.erase(_socketControllers.begin() + i);
				i--;
			}

			readyCount--;
		}

		for (int i = 0; i < _newSocketControllers.size(); i++)
			registerSocketController(_newSocketControllers[i]);
		_newSocketControllers.clear();
	}

	log::i << *this << log::startm << "Stop." << log::endm;
}

void CoreServer::onSocketControllerCreated(SocketController *newController)
{
	_newSocketControllers.push_back(newController);
}

std::ostream& operator<<(std::ostream& stream, const CoreServer& _)
{
	stream << "[CoreServer]";
	return stream;
}