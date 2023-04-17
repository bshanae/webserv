#include "Request.h"

#include <sstream>
#include "utils/exceptions/ParsingException.h"
#include "utils/algo/str.h"
#include "common/path.h"
#include "log/log.h"
#include "common/HeaderName.h"

using namespace webserv;

Optional<Request> Request::parse(const std::string& data)
{
	try
	{
		std::stringstream stream(data);

		Request r;

		stream >> r._method;

		stream >> r._uri;

		const size_t iQuestion = r._uri.find('?');
		if (iQuestion != std::string::npos)
		{
			r._path = directoryRemoteView(r._uri.substr(0, iQuestion));
			r._query = r._uri.substr(iQuestion + 1, r._uri.length() - 1);
		}
		else
		{
			r._path = directoryRemoteView(r._uri);
			r._query = "";
		}

		stream >> r._protocol;

		// drop \r
		stream.get();
		stream.get();

		std::string line;
		while (std::getline(stream, line))
		{
			if (std::isspace(line[0])) // line == \r
				break;

			const HeaderName headerName = HeaderName(line.substr(0, line.find(':')));
			const std::string headerValue = algo::range(line, line.find(' ') + 1, line.length() - 1); // from space till \r

			r._headers[headerName] = headerValue;
		}

		stream >> r._body;

		return r;
	}
	catch (const std::exception& e)
	{
		log::e << "Request" << log::startm << "Parsing error: " << e.what() << log::endm;
		return Optional<Request>();
	}
	catch (...)
	{
		log::e << "Request" << log::startm << "Unknown  parsing error." << log::endm;
		return Optional<Request>();
	}
}

RequestMethod Request::method() const
{
	return _method;
}

const std::string& Request::uri() const
{
	return _uri;
}

const std::string& Request::path() const
{
	return _path;
}

const std::string& Request::query() const
{
	return _query;
}

const std::string& Request::protocol() const
{
	return _protocol;
}

const std::map<HeaderName, std::string>& Request::headers() const
{
	return _headers;
}

const std::string& Request::body() const
{
	return _body;
}

void Request::appendBody(const std::string& bodyPiece)
{
	_body += bodyPiece;
}

Optional<std::string> Request::findHeader(const HeaderName& name) const
{
	typedef std::map<HeaderName, std::string>::const_iterator HeaderIterator;
	for (HeaderIterator i = _headers.cbegin(); i != _headers.cend(); i++)
	{
		if (i->first == name)
			return i->second;
	}

	return Optional<std::string>();
}

Optional<size_t> Request::contentLength() const
{
	Optional<std::string> s = findHeader(HeaderName::ContentLength);
	if (!s)
		return Optional<size_t>();

	return std::stoul(*s);
}

Optional<std::string> Request::hostName() const
{
	Optional<std::string> s = findHeader(HeaderName::Host);
	if (!s)
		return Optional<std::string>();

	const size_t iColon = s->find(':');
	if (iColon == -1)
		return s;

	return algo::range(*s, 0, iColon);
}

bool Request::chunkedEncoding() const
{
	return findHeader(HeaderName::TransferEncoding).valueOr("") == "chunked";
}