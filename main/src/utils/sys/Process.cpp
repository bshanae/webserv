#include "Process.h"

#include <unistd.h>
#include <string>
#include <iostream>
#include "sys.h"
#include "utils/exceptions/InvalidOperationException.h"
#include "utils/exceptions/SystemException.h"

using namespace sys;

Process::Process(const std::string& cmd, const std::vector<std::string>& args, const std::vector<std::string>& env) :
	_stdInStream(NULL),
	_stdOutStream(NULL),
	_stdErrStream(NULL)
{
	_pid = fork();
	if (_pid == -1)
		throw SystemException("Can't fork process!");

	if (_pid == 0)
		ifChild(cmd, args, env);
	else
		ifParent();
}

Process::~Process()
{
	delete _stdInStream;
	delete _stdOutStream;
	delete _stdErrStream;

	sys::close(_stdInPipe.w());
	sys::close(_stdOutPipe.r());
	sys::close(_stdErrPipe.r());
}

FDStream& Process::stdIn()
{
	checkStreamingUsage();
	return *_stdInStream;
}

FDStream& Process::stdOut()
{
	checkStreamingUsage();
	return *_stdOutStream;
}

FDStream& Process::stdErr()
{
	checkStreamingUsage();
	return *_stdErrStream;
}

int Process::wait()
{
	sys::close(_stdInPipe.w());

	int status;
	if (waitpid(_pid, &status, 0) < 0)
		throw SystemException("wait failed!");

	if (!WIFEXITED(status))
		throw SystemException("Child process was aborted!");

	return WEXITSTATUS(status);
}

Process::Process(Process& that)
{
	// deleted
}

Process& Process::operator=(Process& that)
{
	// deleted
	return *this;
}

void Process::ifParent()
{
	sys::close(_stdInPipe.r());
	sys::close(_stdOutPipe.w());
	sys::close(_stdErrPipe.w());

	_stdInStream = new FDStream(_stdInPipe.w());
	_stdOutStream = new FDStream(_stdOutPipe.r());
	_stdErrStream = new FDStream(_stdErrPipe.r());
}

void Process::ifChild(const std::string& cmd, const std::vector<std::string>& args, const std::vector<std::string>& env)
{
	sys::close(_stdInPipe.w());
	sys::close(_stdOutPipe.r());
	sys::close(_stdErrPipe.r());

	::close(sys::stdIn);
	::close(sys::stdOut);
	::close(sys::stdErr);

	sys::transfer(_stdInPipe.r(), sys::stdIn);
	sys::transfer(_stdOutPipe.w(), sys::stdOut);
	sys::transfer(_stdErrPipe.w(), sys::stdErr);

	exec(cmd, args, env);
}

void Process::exec(const std::string& cmd, const std::vector<std::string>& args, const std::vector<std::string>& env)
{
	char* cCmd = const_cast<char*>(cmd.c_str());

	std::vector<char*> cArgv;
	cArgv.reserve(1 + args.size() + 1);
	cArgv.push_back(cCmd);
	for (int i = 0; i < args.size(); i++)
		cArgv.push_back(const_cast<char*>(args[i].c_str()));
	cArgv.push_back(NULL);

	std::vector<char*> cEnv;
	cEnv.reserve(env.size() + 1);
	for (int i = 0; i < env.size(); i++)
		cEnv.push_back(const_cast<char*>(env[i].c_str()));
	cEnv.push_back(NULL);

	if (execve(cCmd, cArgv.data(), cEnv.data()) < 0)
	{
		std::cerr << "execve fail!" << std::endl;
		std::exit(-1);
	}
}

void Process::checkStreamingUsage() const
{
	if (_pid == 0)
		throw InvalidOperationException("Child process doesn't provide streaming interface!");
}