#pragma once

#include <streambuf>
#include <ostream>
#include "FDescriptor.h"

namespace sys
{
	class FDStreamBuffer : public std::streambuf
	{
	public:

		explicit FDStreamBuffer(FDescriptor d);
		virtual ~FDStreamBuffer();

	protected:

		virtual int_type underflow();
		virtual int_type overflow(int_type c);
		virtual int sync();

	private:

		static const size_t bufferSize;

		FDescriptor _fd;
		char* _rBuffer;
		char* _wBuffer;
	};

	class FDStream : private virtual FDStreamBuffer, public std::ostream
	{
	public:

		FDStream(FDescriptor fd);
	};
}