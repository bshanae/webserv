#include <exception>
#include <stdexcept>

class FileException : public std::runtime_error
{
public:

	explicit FileException(const std::string& message);
};
