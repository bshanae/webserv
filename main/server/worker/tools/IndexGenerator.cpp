#include "IndexGenerator.h"

#include <sstream>
#include "tools/fsys/fsys.h"

std::string IndexGenerator::generatePage(Project& project, const std::string& path)
{
	const std::vector<std::string> entries = project.enumerateDirectory(path);

	std::vector<FileDescription> filesDescriptions;
	for (int i = 0; i < entries.size(); i++)
	{
		const std::string& entryName = entries[i];
		const std::string entryPath = fsys::concatPath(path, entryName);

		filesDescriptions.push_back(buildFileDescription(project, entryName, entryPath));
	}
	std::sort(filesDescriptions.begin(), filesDescriptions.end(), compareFileDescription);

	std::stringstream buffer;

	buffer << "<html>\r\n";
	buffer << "<head><title>Index of " << path << "</title></head>\r\n";
	buffer << "<body>\r\n";
	buffer << "<h1>Index of " << path << "</h1><hr><pre>";

	for (int i = 0; i < filesDescriptions.size(); i++)
	{
		const FileDescription &description = filesDescriptions[i];

		buffer << "<a href=\"" + description.path + "\">" + description.displayName + "</a>";

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

bool IndexGenerator::compareFileDescription(const FileDescription& l, const FileDescription& r)
{
	if (l.isDirectory != r.isDirectory)
		return (int)l.isDirectory > (int)r.isDirectory;

	return l.name < r.name;
}

IndexGenerator::FileDescription IndexGenerator::buildFileDescription(Project& project, const std::string& name, const std::string& path)
{
	FileDescription description =
		{
			.path = path,
			.name = name
		};

	description.displayName = description.name;
	if (description.displayName.length() > 50)
	{
		description.displayName.erase(47);
		description.displayName += "..";
	}

	description.isDirectory = project.isDirectory(path);

	struct tm* timeOfModification = project.getTimeOfModification(path);
	char modificationTimeBuffer[32];
	std::strftime(modificationTimeBuffer, 32, "%d-%b-%Y %H:%M", timeOfModification);
	description.modificationTime = modificationTimeBuffer;

	description.sizeInBytes = std::to_string(project.getSizeInBytes(path));

	return description;
}

std::string IndexGenerator::prependWithSpaces(const std::string& content, int length)
{
	return std::string(length - content.length(), ' ') + content;
}