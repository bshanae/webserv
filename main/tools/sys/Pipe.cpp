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

Pipe::Pipe(const Pipe& that) : _fdR(nullFd), _fdW(nullFd)
{
	this->_fds[0] = that._fds[0];
	this->_fds[1] = that._fds[1];
}

Pipe& Pipe::operator=(const Pipe& that)
{
	this->_fds[0] = that._fds[0];
	this->_fds[1] = that._fds[1];

	return *this;
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