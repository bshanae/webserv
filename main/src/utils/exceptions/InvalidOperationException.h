#include <exception>
#include <stdexcept>

class InvalidOperationException : public std::runtime_error
{
public:
	explicit InvalidOperationException(const std::string& message);
	InvalidOperationException();
};
