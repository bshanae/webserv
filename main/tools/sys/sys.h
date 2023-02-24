#pragma once

#include <string>

namespace sys
{
	extern bool TerminationRequested;
	void listenForTermination();

	std::string concatPath(const std::string& a, const std::string& b);
}