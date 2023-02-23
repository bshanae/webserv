#pragma once

#include <string>

class Request
{
public:

	enum Method
	{
		GET
	};

	static Request parse(const std::string& data);

	Request(const Request& that);
	Request& operator=(const Request& that);

	Method getMethod() const;
	std::string getUrl() const;
	std::string getHttpVersion() const;

private:

	Method _method;
	std::string _url;
	std::string _httpVersion;

	Request(Method type, const std::string& url, const std::string& httpVersion);
};
