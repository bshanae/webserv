#pragma once

#include <string>
#include "Project.h"

namespace webserv
{
	class IndexGenerator;
}

class webserv::IndexGenerator
{
public:

	static std::string generatePage(Project& project, const std::string& remotePath, const std::string& localPath);

private:

	struct FileInfo
	{
		std::string remotePath;
		std::string name;
		std::string displayName;
		bool isDirectory;
		std::string modificationTime;
		std::string sizeInBytes;
	};

	static bool compareFileInfo(const FileInfo& l, const FileInfo &r);
	static FileInfo buildFileInfo(Project& project, const std::string& name, const std::string& remotePath, const std::string& localPath);
	static std::string prependWithSpaces(const std::string& content, int length);
};