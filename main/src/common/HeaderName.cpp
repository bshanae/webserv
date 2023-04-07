#include "HeaderName.h"

#include "utils/exceptions/ParsingException.h"
#include "utils/exceptions/InvalidArgumentException.h"

using namespace webserv;

HeaderName HeaderName::Date = HeaderName("Date");
HeaderName HeaderName::Server = HeaderName("Server");
HeaderName HeaderName::ContentLength = HeaderName("Content-Length");
HeaderName HeaderName::ContentType = HeaderName("Content-Type");

HeaderName::HeaderName()
{
}

HeaderName::HeaderName(const std::string& string) : std::string(string)
{
}

HeaderName::HeaderName(const char* string) : std::string(string)
{
}