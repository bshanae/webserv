#pragma once

#include <string>

class Request
{
public:

	enum Type
	{
		GET
	};

	static Request parse(const std::string& data);

	Request(const Request& that);
	Request& operator=(const Request& that);

	Type getType() const;
	std::string getUrl() const;
	std::string getHttpVersion() const;

private:

	Type _type;
	std::string _url;
	std::string _httpVersion;

	Request(Type type, const std::string& url, const std::string& httpVersion);
};
