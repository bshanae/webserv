#pragma once

#include <string>
#include "context/Context.h"

class IndexGenerator
{
public:

	static std::string generatePage(Project& project, const std::string& path);

private:

	struct FileDescription
	{
		std::string path;
		std::string name;
		std::string displayName;
		bool isDirectory;
		std::string modificationTime;
		std::string sizeInBytes;
	};

	static bool compareFileDescription(const FileDescription& l, const FileDescription &r);
	static FileDescription buildFileDescription(Project& project, const std::string& name, const std::string& path);
	static std::string prependWithSpaces(const std::string& content, int length);
};