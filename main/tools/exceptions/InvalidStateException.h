#include <exception>
#include <stdexcept>

class InvalidStateException : public std::runtime_error
{
public:

	explicit InvalidStateException(const std::string& message);
	InvalidStateException();
};
