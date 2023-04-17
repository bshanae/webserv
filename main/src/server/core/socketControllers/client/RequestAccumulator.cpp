#include "RequestAccumulator.h"

#include <sstream>
#include "utils/algo/str.h"

using namespace webserv;

Optional<Request>  RequestAccumulator::accumulate(const std::string& data)
{
	if (_tmpRequest)
	{
		return accumulateBody(data);
	}
	else
	{
		_requestBuffer += data;

		const size_t iHeaderEnd = _requestBuffer.find("\r\n\r\n");
		if (iHeaderEnd != -1)
		{
			_tmpRequest = Request::parse(_requestBuffer.substr(0, iHeaderEnd + 2));
			const std::string leftoverBuffer = algo::range(_requestBuffer, iHeaderEnd + 4, _requestBuffer.length());

			_requestBuffer.clear();

			return accumulateBody(leftoverBuffer);
		}
	}

	return Optional<Request>();
}

Optional<Request> RequestAccumulator::accumulateBody(const std::string& bodyPiece)
{
	bool bodyComplete = false;

	if (_tmpRequest->chunkedEncoding())
	{
		_bodyBuffer += bodyPiece;

		Optional<std::string> chunk;
		while ((chunk = accumulateChunk()))
		{
			if (chunk->length() == 0)
			{
				bodyComplete = true;
				_bodyBuffer.clear();
			}

			_tmpRequest->appendBody(*chunk);
		}
	}
	else
	{
		_tmpRequest->appendBody(bodyPiece);
		bodyComplete = _tmpRequest->contentLength().valueOr(0) >= _tmpRequest->body().size();
	}

	if (bodyComplete)
		return _tmpRequest.transfer();

	return Optional<Request>();
}

Optional<std::string> RequestAccumulator::accumulateChunk()
{
	if (_bodyBuffer.length() == 0)
		return Optional<std::string>();

	const size_t iPayloadStart = _bodyBuffer.find("\r\n") + 2;
	if (iPayloadStart == -1)
		return Optional<std::string>();

	std::istringstream chunkSizeSStream(algo::range(_bodyBuffer, 0, iPayloadStart - 2));
	size_t chunkSize;
	chunkSizeSStream >> std::hex >> chunkSize;
	if (_bodyBuffer.size() - iPayloadStart - 2 < chunkSize)
		return Optional<std::string>();

	const size_t iPayloadEnd = _bodyBuffer.find("\r\n", iPayloadStart);
	if (iPayloadEnd == -1)
		return Optional<std::string>();

	if (chunkSize != iPayloadEnd - iPayloadStart)
		throw InvalidStateException("Chunk size is invalid");

	const std::string chunk = algo::range(_bodyBuffer, iPayloadStart, iPayloadEnd);

	_bodyBuffer = algo::range(_bodyBuffer, iPayloadEnd + 2, _bodyBuffer.length());

	return chunk;
}