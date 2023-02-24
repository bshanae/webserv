#include <exception>
#include <stdexcept>

class InvalidUsageException : public std::runtime_error
{
public:
	explicit InvalidUsageException(const std::string& message);
	InvalidUsageException();
};
