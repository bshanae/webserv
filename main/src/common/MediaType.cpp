#include "MediaType.h"

#include <unordered_map>
#include "utils/exceptions/ParsingException.h"

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