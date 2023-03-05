#include "FDescriptor.h"

namespace sys
{
	sys::FDescriptor nullFd = -1;
	sys::FDescriptor stdIn = 0;
	sys::FDescriptor stdOut = 1;
	sys::FDescriptor stdErr = 2;

	bool validDescriptor(FDescriptor descriptor)
	{
		return descriptor != nullFd;
	}
}