#pragma once

#include <string>

class MediaType : public std::string
{
public:

	static MediaType Default;
	static MediaType Html;

	static MediaType fromFileExtension(const std::string& fileExtension);

	MediaType();
	explicit MediaType(const std::string& string);
	MediaType(const char* string);
	MediaType(const MediaType& that);
	MediaType& operator=(const MediaType& that);
};