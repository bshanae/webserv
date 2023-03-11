#include "IndexGenerator.h"

#include <sstream>
#include "utils/sys/sys.h"
#include "utils/sys/sys.path.h"

using namespace webserv;

std::string IndexGenerator::generatePage(Project& project, const std::string& remotePath, const std::string& localPath)
{
	const std::vector<std::string> entries = sys::enumerateDirectory(localPath);

	std::vector<FileInfo> fileInfos;
	for (int i = 0; i < entries.size(); i++)
	{
		const std::string& entryName = entries[i];
		const std::string remoteEntryPath = sys::path::concat(remotePath, entryName);
		const std::string localEntryPath = project.resolvePath(remoteEntryPath);

		fileInfos.push_back(buildFileInfo(project, entryName, remoteEntryPath, localEntryPath));
	}
	std::sort(fileInfos.begin(), fileInfos.end(), compareFileInfo);

	std::stringstream buffer;

	buffer << "<html>\r\n";
	buffer << "<head><title>Index of " << remotePath << "</title></head>\r\n";
	buffer << "<body>\r\n";
	buffer << "<h1>Index of " << remotePath << "</h1><hr><pre>";

	for (int i = 0; i < fileInfos.size(); i++)
	{
		const FileInfo &description = fileInfos[i];

		buffer << "<a href=\"" + description.remotePath + "\">" + description.displayName + "</a>";

		if (description.name != "..")
		{
			buffer << std::string(68 - description.displayName.length(), ' ');

			buffer << description.modificationTime;
			if (description.isDirectory)
				buffer << prependWithSpaces("-", 20);
			else
				buffer << prependWithSpaces(description.sizeInBytes, 20);
		}

		buffer << "\r\n";
	}

	buffer << "</pre><hr></body>\r\n";
	buffer << "</html>\r\n";

	return buffer.str();
}

bool IndexGenerator::compareFileInfo(const FileInfo& l, const FileInfo& r)
{
	if (l.isDirectory != r.isDirectory)
		return (int)l.isDirectory > (int)r.isDirectory;

	return l.name < r.name;
}

IndexGenerator::FileInfo IndexGenerator::buildFileInfo(Project& project, const std::string& name, const std::string& remotePath, const std::string& localPath)
{
	FileInfo info = {
		.remotePath = remotePath,
		.name = name
	};

	info.displayName = info.name;
	if (info.displayName.length() > 50)
	{
		info.displayName.erase(47);
		info.displayName += "..";
	}

	info.isDirectory = sys::isDirectory(localPath);

	struct tm* timeOfModification = sys::modificationTime(localPath);
	char modificationTimeBuffer[32];
	std::strftime(modificationTimeBuffer, 32, "%d-%b-%Y %H:%M", timeOfModification);
	info.modificationTime = modificationTimeBuffer;

	info.sizeInBytes = std::to_string(sys::sizeInBytes(localPath));

	return info;
}

std::string IndexGenerator::prependWithSpaces(const std::string& content, int length)
{
	return std::string(length - content.length(), ' ') + content;
}