#include "Pipe.h"

#include <unistd.h>
#include <string>
#include "tools/exceptions/SystemException.h"

using namespace sys;

Pipe::Pipe() : _fdR(nullFd), _fdW(nullFd)
{
	if (pipe(_fds) < 0)
		throw SystemException("Can't create pipe!");
}

FDescriptor& Pipe::r()
{
	return _fdR;
}

FDescriptor Pipe::r() const
{
	return _fdR;
}

FDescriptor& Pipe::w()
{
	return _fdW;
}

FDescriptor Pipe::w() const
{
	return _fdW;
}