#include "RequestAccumulator.h"

#include "utils/algo/str.h"

using namespace webserv;

bool RequestAccumulator::requestReady() const
{
	return _finalRequest.hasValue();
}

Optional<Request> RequestAccumulator::request()
{
	Optional<Request> result = _finalRequest;
	_finalRequest = Optional<Request>();

	return result;
}

void RequestAccumulator::accumulate(const std::string& data)
{
	if (!_tmpRequest)
	{
		_tmpBuffer += data;

		const size_t iHeaderEnd = _tmpBuffer.find("\r\n\r\n");
		if (iHeaderEnd != -1)
		{
			_tmpRequest = Request::parse(_tmpBuffer.substr(0, iHeaderEnd + 2));
			_tmpRequest->appendBody(algo::range(_tmpBuffer, iHeaderEnd + 4, _tmpBuffer.length()));

			_tmpBuffer = "";

			tryBuildFinalRequest();
		}
	}
	else
	{
		_tmpRequest->appendBody(data);
		tryBuildFinalRequest();
	}
}

void RequestAccumulator::tryBuildFinalRequest()
{
	if (!_tmpRequest)
		return;

	if (_tmpRequest->contentLength().valueOr(0) > _tmpRequest->body().size())
		return;

	_finalRequest = _tmpRequest;
	_tmpRequest = Optional<Request>();
}