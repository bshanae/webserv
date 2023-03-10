#include <exception>
#include <stdexcept>

class SystemException : public std::runtime_error
{
public:

	explicit SystemException(const std::string& message);
};
