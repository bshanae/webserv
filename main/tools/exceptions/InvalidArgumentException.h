#include <exception>
#include <stdexcept>

class InvalidArgumentException : public std::runtime_error
{
public:
	explicit InvalidArgumentException(const std::string& argumentName);
	InvalidArgumentException();
};
