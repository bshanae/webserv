#include "sys.h"

#include <csignal>
#include <unistd.h>
#include <dirent.h>
#include <string>
#include <fstream>
#include <sstream>
#include "utils/exceptions/FileException.h"
#include "utils/exceptions/InvalidArgumentException.h"

using namespace sys;

bool sys::TerminationRequested = false;

static void handlerInterrupt(int)
{
	TerminationRequested = true;
}

void sys::listenForTermination()
{
	signal(SIGINT, handlerInterrupt);
}

void sys::close(FDescriptor& fd)
{
	if (fd == nullFd)
		return;

	::close(fd);
	fd = nullFd;
}

void sys::transfer(FDescriptor& from, FDescriptor to)
{
	dup2(from, to);
	close(from);
}

struct stat sys::stat(const std::string &absolutePath)
{
	struct stat s;
	if (::stat(absolutePath.c_str(), &s) != 0)
		throw FileException("Can't get stat of file " + absolutePath);

	return s;
}


tm* sys::modificationTime(const std::string& path)
{
	const struct stat s = stat(path);
	return gmtime(&s.st_mtime);
}

long sys::sizeInBytes(const std::string& path)
{
	return stat(path).st_size;
}

std::string sys::readFile(const std::string& path)
{
	if (path.length() == 0)
		throw InvalidArgumentException("path");

	std::ifstream file(path);
	if (!file)
		throw FileException("File not found: " + path);

	std::stringstream stream;
	stream << file.rdbuf();

	return stream.str();
}

bool sys::isFile(const std::string& path)
{
	return (stat(path).st_mode & S_IFREG) != 0;
}

bool sys::isDirectory(const std::string& path)
{
	return (stat(path).st_mode & S_IFDIR) != 0;
}

std::vector<std::string> sys::enumerateDirectory(const std::string& path)
{
	DIR* dirDescriptor = opendir(path.c_str());
	if (dirDescriptor == NULL)
		return std::vector<std::string>();

	std::vector<std::string> entries;

	struct dirent* entryDescriptor;
	while ((entryDescriptor = readdir(dirDescriptor)) != NULL)
	{
		const std::string entryName = entryDescriptor->d_name;
		if (entryName == "." || entryName == "..")
			continue;

		entries.push_back(entryName);
	}

	closedir(dirDescriptor);

	return entries;
}