#include "sys.h"

#include <csignal>
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <string>
#include <fstream>
#include <sstream>
#include "utils/exceptions/FileException.h"
#include "utils/exceptions/SystemException.h"
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

std::string sys::execute(
	const std::string& cmd,
	const std::vector<std::string>& arg,
	const std::vector<std::string>& env,
	const std::string& in
)
{
	std::string out;

	int stdinDup = dup(sys::stdIn);
	int stdoutDup = dup(sys::stdOut);

	FILE* fIn = tmpfile();
	FILE* fOut = tmpfile();
	int fdIn = fileno(fIn);
	int fdOut = fileno(fOut);

	write(fdIn, in.c_str(), in.size());
	lseek(fdIn, 0, SEEK_SET);

	pid_t pid = fork();
	if (pid == -1)
		throw SystemException("fork failed");

	if (pid == 0)
	{
		// child

		dup2(fdIn, sys::stdIn);
		dup2(fdOut, sys::stdOut);

		const char* cCmd = cmd.c_str();

		std::vector<char*> cArgv;
		cArgv.reserve(1 + arg.size() + 1);
		cArgv.push_back((char*)cCmd);
		for (int i = 0; i < arg.size(); i++)
			cArgv.push_back(const_cast<char*>(arg[i].c_str()));
		cArgv.push_back(NULL);

		std::vector<char*> cEnv;
		cEnv.reserve(env.size() + 1);
		for (int i = 0; i < env.size(); i++)
			cEnv.push_back(const_cast<char*>(env[i].c_str()));
		cEnv.push_back(NULL);

		if (execve(cCmd, cArgv.data(), cEnv.data()) < 0)
			throw SystemException("execve failed");
	}
	else
	{
		//parent

		static const int buf_size = 65536;
		char buffer[buf_size] = { 0 };

		waitpid(-1, NULL, 0);
		lseek(fdOut, 0, SEEK_SET);

		for (;;)
		{
			memset(buffer, 0, buf_size);

			const int nRead = read(fdOut, buffer, buf_size - 1);
			if (nRead == 0)
				break;

			out += buffer;
		}
	}

	dup2(stdinDup, sys::stdIn);
	dup2(stdoutDup, sys::stdOut);

	fclose(fIn);
	fclose(fOut);

	close(fdIn);
	close(fdOut);
	close(stdinDup);
	close(stdoutDup);

	if (pid == 0)
		exit(0);

	return out;
}

Optional<struct stat> sys::stat(const std::string &absolutePath)
{
	struct stat s;
	if (::stat(absolutePath.c_str(), &s) == 0)
		return s;

	return Optional<struct stat>();
}


tm* sys::modificationTime(const std::string& path)
{
	const Optional<struct stat> s = stat(path);
	if (!s)
		throw FileException("Can't get modification time. Invalid path.");

	return gmtime(&s->st_mtime);
}

long sys::sizeInBytes(const std::string& path)
{
	const Optional<struct stat> s = stat(path);
	if (!s)
		throw FileException("Can't get size in bytes. Invalid path.");

	return s->st_size;
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
	const Optional<struct stat> s = stat(path);
	if (!s)
		return false;

	return (stat(path)->st_mode & S_IFREG) != 0;
}

bool sys::isDirectory(const std::string& path)
{
	const Optional<struct stat> s = stat(path);
	if (!s)
		return false;

	return (stat(path)->st_mode & S_IFDIR) != 0;
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

bool sys::remove(const std::string& path)
{
	return std::remove(path.c_str()) == 0;
}