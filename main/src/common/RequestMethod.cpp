#include "RequestMethod.h"

#include <istream>
#include <unordered_map>
#include <map>
#include "utils/algo/str.h"
#include "utils/exceptions/ParsingException.h"
#include "utils/exceptions/InvalidArgumentException.h"

using namespace webserv;

std::istream& operator>>(std::istream& stream, RequestMethod& method)
{
	static std::unordered_map<std::string, RequestMethod> lookup;
	if (lookup.empty())
	{
		lookup["get"] = RequestMethodGET;
		lookup["put"] = RequestMethodPUT;
		lookup["post"] = RequestMethodPOST;
		lookup["delete"] = RequestMethodDELETE;
	}

	std::string str;
	stream >> str;
	algo::toLower(str);

	std::unordered_map<std::string, RequestMethod>::iterator i = lookup.find(str);
	if (i == lookup.end())
		throw ParsingException("Can't parse request method!");

	method = i->second;

	return stream;
}

std::string toString(RequestMethod method)
{
	static std::map<RequestMethod, std::string> lookup;
	if (lookup.empty())
	{
		lookup[RequestMethodGET] = "GET";
		lookup[RequestMethodPUT] = "PUT";
		lookup[RequestMethodPOST] = "POST";
	}

	std::map<RequestMethod, std::string>::iterator i = lookup.find(method);
	if (i == lookup.end())
		throw InvalidArgumentException("Can't convert request method to string!");

	return i->second;
}