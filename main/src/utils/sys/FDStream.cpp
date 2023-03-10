#include "FDStream.h"

#include <cassert>
#include <streambuf>
#include <new>
#include <unistd.h>
#include "utils/exceptions/SystemException.h"

using namespace sys;

const size_t FDStreamBuffer::bufferSize = 4096;

FDStreamBuffer::FDStreamBuffer(FDescriptor d) : _fd(d), _rBuffer(NULL), _wBuffer(NULL)
{
}

FDStreamBuffer::~FDStreamBuffer()
{
	setg(0, 0, 0);
	setp(0, 0);

	delete[] _rBuffer;
	_rBuffer = NULL;

	delete[] _wBuffer;
	_wBuffer = NULL;

	_fd = nullFd;
}

FDStreamBuffer::int_type FDStreamBuffer::underflow()
{
	assert(gptr() == egptr());

	if (!validDescriptor(_fd))
		return traits_type::eof();

	if (_rBuffer)
	{
		*_rBuffer = *(gptr() - 1);
	}
	else
	{
		_rBuffer = new(std::nothrow) char[bufferSize];
		if (!_rBuffer)
			return traits_type::eof();
	}

	int nRead = read(_fd, _rBuffer + 1, bufferSize - 1);
	if (nRead <= 0)
		return traits_type::eof();

	setg(_rBuffer, _rBuffer + 1, _rBuffer + 1 + nRead);

	return traits_type::to_int_type(*gptr());
}

FDStreamBuffer::int_type FDStreamBuffer::overflow(int_type c)
{
	assert(pptr() == epptr());

	if (_fd < 0)
		return traits_type::eof();

	if (!_wBuffer)
	{
		_wBuffer = new(std::nothrow) char[bufferSize];
		if (!_wBuffer)
			return traits_type::eof();
	}

	if (c == traits_type::eof() || sync() == -1)
		return traits_type::eof();

	*pptr() = traits_type::to_char_type(c);
	pbump(1);

	return c;
}

int FDStreamBuffer::sync()
{
	if (!validDescriptor(_fd) || !_wBuffer)
		return 0;

	char* p = pbase();
	while (p < pptr())
	{
		int nWritten = write(_fd, p, pptr() - p);
		if (nWritten <= 0)
			return -1;

		p += nWritten;
	}

	setp(_wBuffer, _wBuffer + bufferSize);

	return 0;
}

FDStream::FDStream(FDescriptor fd) :
	FDStreamBuffer(fd),
	std::ios(static_cast<std::streambuf*>(this)), std::ostream(static_cast<std::streambuf*>(this))
{
}