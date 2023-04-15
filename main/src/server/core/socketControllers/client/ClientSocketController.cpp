#include "ClientSocketController.h"

#include <unistd.h>
#include "log/log.h"
#include "utils/algo/str.h"

using namespace webserv;
using namespace webserv::log;

ClientSocketController::ClientSocketController(sys::FDescriptor socket, const WebAddress& address):
	_delegate(NULL),
	_address(address), // NOLINT(cppcoreguidelines-pro-type-member-init)
	_readBuffer(512),
	_writeBuffer(512)
{
	bindSocket(socket);

	log::i << *this << log::startm << "Initialized." << log::endm;
}

ClientSocketController::~ClientSocketController()
{
	log::i << *this << log::startm << "Uninitialized." << log::endm;
}

const WebAddress& ClientSocketController::address() const
{
	return _address;
}

void ClientSocketController::setDelegate(IClientSocketDelegate* delegate)
{
	_delegate = delegate;
}

void ClientSocketController::processSocketEvent(SocketEvent event)
{
	if (event == SocketEventCanRead)
		processCanReadEvent();
	if (event == SocketEventCanWrite)
		processCanWriteEvent();
}

void ClientSocketController::processCanReadEvent()
{
	Optional<std::string> data = readFromSocket();
	if (!data)
	{
		log::w << *this << log::startm << "Connection closed." << log::endm;

		unbindSocket();

		if (_delegate != NULL)
			_delegate->onClientDisconnected(_address);

		return;
	}

	Optional<Request> request = processRequest(*data);
	if (!request)
		return;

	Optional<std::string> response = processResponse(*request);
	if (!response)
		return;

	saveResponse(*response);
}

void ClientSocketController::processCanWriteEvent()
{
	flushResponses();
}

Optional<std::string> ClientSocketController::readFromSocket()
{
	for (;;)
	{
		const ssize_t readSize = read(socket(), _readBuffer.writePtr(), _readBuffer.availableWriteSize());
		_readBuffer.didWrite(readSize);

		if (readSize == 0)
			return Optional<std::string>();

		if (!_readBuffer.full())
			break;

		_readBuffer.willWrite(512);
	}

	_readBuffer.write("\0", 1);

	std::string m = std::string(_readBuffer.readPtr());
	_readBuffer.didRead(_readBuffer.availableReadSize());

	logRequest(m);

	_readBuffer.pack();

	return m;
}

Optional<Request> ClientSocketController::processRequest(const std::string& data)
{
	_requestAccumulator.accumulate(data);

	if (_requestAccumulator.requestReady())
		return _requestAccumulator.request();
	else
		return Optional<Request>();
}

Optional<std::string> ClientSocketController::processResponse(const Request& request)
{
	Response r = _delegate->respondToRequest(request);

	const std::string rStr = r.build();
	logResponse(rStr);

	return rStr;
}

void ClientSocketController::saveResponse(const std::string& message)
{
	_writeBuffer.write(message.data(), message.size());
}

void ClientSocketController::flushResponses()
{
	if (_writeBuffer.availableReadSize() == 0)
		return;

	const size_t writtenSize = write(socket(), _writeBuffer.readPtr(), _writeBuffer.availableReadSize());
	_writeBuffer.didRead(writtenSize);

	_writeBuffer.pack();
}

void ClientSocketController::logRequest(const std::string& str) const
{
	if (!log::v.enabled)
		return;

	std::string markedStr = algo::truncate(str, 500);
	algo::markEndl(markedStr, "\r\n");

	log::v << *this << log::startm << "REQUEST" << log::endl
		   << markedStr << log::endm;
}

void ClientSocketController::logResponse(const std::string& str) const
{
	if (!log::v.enabled)
		return;

	std::string markedStr = algo::truncate(str, 500);
	algo::markEndl(markedStr, "\r\n");

	log::v << *this << log::startm << "RESPONSE" << log::endl
		   << markedStr << log::endm;
}

std::ostream& operator<<(std::ostream& stream, const ClientSocketController& controller)
{
	stream << "[ClientSocketController:socket=" << controller.socket() << ",address=" << controller._address << "]";
	return stream;
}