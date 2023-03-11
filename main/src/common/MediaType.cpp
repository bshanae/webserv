#include "MediaType.h"

#include "utils/exceptions/ParsingException.h"

using namespace webserv;

MediaType MediaType::Default = MediaType("text/html");
MediaType MediaType::Html = MediaType("text/html");

MediaType::MediaType()
{
}

MediaType::MediaType(const std::string& string) : std::string(string)
{
}

MediaType::MediaType(const char* string) : std::string(string)
{
}