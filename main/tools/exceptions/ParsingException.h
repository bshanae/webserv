#include <exception>
#include <stdexcept>

class ParsingException : public std::runtime_error
{
public:

	explicit ParsingException(const std::string& message);
};
