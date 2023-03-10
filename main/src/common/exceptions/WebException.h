#include <exception>
#include <stdexcept>

#include "common/StatusCode.h"

class WebException : public std::runtime_error
{
public:

	explicit WebException(StatusCode code, const std::string& cause = "");

	StatusCode code() const;

private:

	StatusCode _code;
};
