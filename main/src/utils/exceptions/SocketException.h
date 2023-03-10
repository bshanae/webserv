#include <exception>
#include <stdexcept>

class SocketException : public std::runtime_error
{
public:
	explicit SocketException(const std::string& message);
	SocketException();
};
