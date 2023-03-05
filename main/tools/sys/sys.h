#pragma once

#include "FDescriptor.h"

namespace sys
{
	extern bool TerminationRequested;
	void listenForTermination();

	void close(FDescriptor& fd);
	void transfer(FDescriptor& fdFrom, FDescriptor fdTo);
}