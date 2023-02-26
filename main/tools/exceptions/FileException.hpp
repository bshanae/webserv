#include <exception>
#include <stdexcept>

class FileException : public std::runtime_error
{
public:
	FileException(const std::string& message);
	FileException();
};
