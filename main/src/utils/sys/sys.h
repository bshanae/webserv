#pragma once

#include <sys/stat.h>
#include <vector>
#include "FDescriptor.h"
#include "utils/templates/Optional.h"

namespace sys
{
	extern bool TerminationRequested;
	void listenForTermination();

	void close(FDescriptor& fd);
	void transfer(FDescriptor& fdFrom, FDescriptor fdTo);

	Optional<struct stat> stat(const std::string &absolutePath);
	tm* modificationTime(const std::string& path);
	long sizeInBytes(const std::string& path);
	std::string readFile(const std::string& path);
	bool isFile(const std::string& path);
	bool isDirectory(const std::string& path);
	std::vector<std::string> enumerateDirectory(const std::string& path);
}