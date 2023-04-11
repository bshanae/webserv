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

	bool requestReady() const;
	Optional<Request> request();
	void accumulate(const std::string& message);

private:

	std::string _tmpBuffer;
	Optional<Request> _tmpRequest;
	Optional<Request> _finalRequest;

	void tryBuildFinalRequest();
};