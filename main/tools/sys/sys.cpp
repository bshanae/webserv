#include "sys.h"

#include <csignal>
#include <unistd.h>

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