#include <exception>
#include <stdexcept>

#include "common/StatusCode.h"

namespace webserv
{
	class WebException;
}

class webserv::WebException : public std::runtime_error
{
public:

	explicit WebException(StatusCode code, const std::string& cause = "");

	StatusCode code() const;

private:

	StatusCode _code;
};
