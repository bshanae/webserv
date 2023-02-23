#pragma once

#include <string>
#include <sstream>

class Response
{
public:

	void addHeader();
	void addBody(const std::string& data);

	std::string build() const;

private:

	std::ostringstream _buffer;
};
