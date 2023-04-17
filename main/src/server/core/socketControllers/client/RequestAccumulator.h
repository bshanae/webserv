#pragma once

#include <string>
#include "server/core/messages/Request.h"

namespace webserv
{
	class RequestAccumulator;
}

class webserv::RequestAccumulator
{
public:

	Optional<Request> accumulate(const std::string& data);

private:

	std::string _requestBuffer;
	std::string _bodyBuffer;
	Optional<Request> _tmpRequest;

	Optional<Request> accumulateBody(const std::string& bodyPiece);
	Optional<std::string> accumulateChunk();
};