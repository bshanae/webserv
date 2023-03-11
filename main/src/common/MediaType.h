#pragma once

#include <string>

namespace webserv
{
	class MediaType;
}

class webserv::MediaType : public std::string
{
public:

	static MediaType Default;
	static MediaType Html;

	MediaType();
	explicit MediaType(const std::string& string);
	MediaType(const char* string);
};
