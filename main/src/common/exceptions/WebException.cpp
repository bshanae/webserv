#include "WebException.h"

using namespace webserv;

WebException::WebException(StatusCode code, const std::string& cause) : std::runtime_error(cause), _code(code)
{
}

StatusCode WebException::code() const
{
	return _code;
}