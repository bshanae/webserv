#include <exception>
#include <stdexcept>

class ItemNotFoundException : public std::runtime_error
{
public:
	explicit ItemNotFoundException(const std::string& message);
	ItemNotFoundException();
};