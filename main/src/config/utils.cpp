#include "utils.h"

using namespace webserv::config::utils;

bool webserv::config::utils::isIgnored(const std::string& line)
{
	return line.length() == 0 || line[0] == '#';
}

bool webserv::config::utils::isBlockEnd(const std::string& line)
{
	return line[0] == '}';
}

bool webserv::config::utils::getLine(std::istream& stream, std::string& line)
{
	if (!std::getline(stream, line))
		return false;

	line = algo::ltrim(line);
	return true;
}

std::vector<std::string> webserv::config::utils::breakLine(const std::string& line)
{
	std::vector<std::string> words;

	std::istringstream iss(line);
	std::string word;
	while (getline(iss, word, ' '))
		words.push_back(word);

	return words;
}

std::string webserv::config::utils::extractArgument(const std::string& line)
{
	size_t i = line.find(' ');
	if (i == -1)
		throw ParsingException("Space not found.");

	return line.substr(i + 1, line.length() - 1);
}

std::vector<std::string> webserv::config::utils::extractArguments(const std::string& line)
{
	size_t i = line.find(' ');
	if (i == -1)
		throw ParsingException("Space not found.");

	std::vector<std::string> args;

	size_t argBegin = i + 1;
	size_t argEnd = -1;
	while (argEnd != line.length())
	{
		argEnd = line.find(',', argBegin);
		if (argEnd == -1)
			argEnd = line.find(' ', argBegin);
		if (argEnd == -1)
			argEnd = line.length();

		args.push_back(algo::range(line, argBegin, argEnd));

		argBegin = argEnd + 1;
		algo::pass(line, argBegin, ' ');
	}

	return args;
}