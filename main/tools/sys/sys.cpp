#include "sys.h"

#include <csignal>

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

std::string sys::concatPath(const std::string& a, const std::string& b)
{
	if (a.empty())
		return b;
	if (b.empty())
		return a;

	if (a[a.length() - 1] == '/' || b[0] == '/')
		return a + b;
	else
		return a + '/' + b;
}