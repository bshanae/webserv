#include "Request.h"

#include <sstream>
#include "utils/exceptions/ParsingException.h"
#include "utils/algo/str.h"
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
			r._path = r._uri.substr(0, iQuestion);
			r._query = r._uri.substr(iQuestion + 1, r._uri.length() - 1);
		}
		else
		{
			r._path = r._uri;
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
			const std::string headerValue = algo::range(line, line.find(' '), line.length() - 1); // from space till \r

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