#include <exception>
#include <stdexcept>

class FileNotFoundException : public std::runtime_error
{
public:
	explicit FileNotFoundException(const std::string& fileName);
};
