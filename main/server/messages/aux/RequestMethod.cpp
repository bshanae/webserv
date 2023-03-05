#include "RequestMethod.h"

#include <istream>
#include <unordered_map>
#include <map>
#include "tools/algo/str.h"
#include "tools/exceptions/ParsingException.h"
#include "tools/exceptions/InvalidArgumentException.h"

std::istream& operator>>(std::istream& stream, RequestMethod& method)
{
	static std::unordered_map<std::string, RequestMethod> lookup;
	if (lookup.empty())
	{
		lookup["get"] = RequestMethodGET;
		lookup["put"] = RequestMethodPUT;
		lookup["post"] = RequestMethodPOST;
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

std::string to_string(RequestMethod method)
{
	static std::map<RequestMethod, std::string> lookup;
	if (lookup.empty())
	{
		lookup[RequestMethodGET] = "get";
		lookup[RequestMethodPUT] = "put";
		lookup[RequestMethodPOST] = "post";
	}

	std::map<RequestMethod, std::string>::iterator i = lookup.find(method);
	if (i == lookup.end())
		throw InvalidArgumentException("Can't convert request method to string!");

	return i->second;
}