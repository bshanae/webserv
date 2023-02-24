#include "Project.h"

#include <dirent.h>
#include <fstream>
#include <sstream>
#include <ctime>
#include "tools/log/log.h"
#include "tools/sys/sys.h"
#include "tools/exceptions/FileNotFoundException.h"
#include "tools/exceptions/InvalidArgumentException.h"

Project::Project(const Config& config)
{
	_root = config.getProjectRoot();
}

Project::Project(const Project& that)
{
	*this = that;
}

Project& Project::operator=(const Project& that)
{
	_root = that._root;
	return *this;
}

struct tm *Project::getTimeOfModification(const std::string& path) const
{
	const Optional<struct stat> s = getStat(sys::concatPath(_root, path));
	if (!s.hasValue())
		return NULL;

	return gmtime(&s->st_mtime);
}

long Project::getSizeInBytes(const std::string& path) const
{
	const Optional<struct stat> s = getStat(sys::concatPath(_root, path));
	if (!s.hasValue())
		return 0;

	return s->st_size;
}

std::string Project::readFile(const std::string& path) const
{
	if (path.length() == 0)
	{
		log::e << log::entity << "Project" << log::endl
			   << "Path is empty!" << log::endm;
		throw InvalidArgumentException("path");
	}

	const std::string absolutePath = sys::concatPath(_root, path);

	std::ifstream file(absolutePath);
	if (!file)
	{
		log::e << log::entity << "Project" << log::endl
			   << "Can't open file at '" << absolutePath << "'" << log::endm;
		throw FileNotFoundException(path);
	}

	std::stringstream stream;
	stream << file.rdbuf();

	return stream.str();
}

bool Project::isDirectory(const std::string& path) const
{
	const Optional<struct stat> s = getStat(sys::concatPath(_root, path));
	if (!s.hasValue())
		return false;

	return (s->st_mode & S_IFDIR) != 0;
}

std::vector<std::string> Project::enumerateDirectory(const std::string& path) const
{
	const std::string absolutePath = sys::concatPath(_root, path);

	DIR* dirDescriptor = opendir(absolutePath.c_str());
	if (dirDescriptor == NULL)
	{
		log::e << log::entity << *this << log::endl
			   << "Can't read directory" << log::endm;
		return std::vector<std::string>();
	}

	std::vector<std::string> entries;

	struct dirent* entryDescriptor;
	while ((entryDescriptor = readdir(dirDescriptor)) != NULL)
	{
		const std::string entryName = entryDescriptor->d_name;
		if (entryName == ".")
			continue;

		entries.push_back(entryName);
	}

	closedir(dirDescriptor);

	return entries;
}

std::ostream& operator<<(std::ostream& stream, const Project& project)
{
	stream << "Project(root=" << project._root << ")";
	return stream;
}

Optional<struct stat> Project::getStat(const std::string &absolutePath) const
{
	struct stat s;
	if (stat(absolutePath.c_str(), &s) != 0)
	{
		log::w << log::entity << *this << log::endl
			   << "Can't get stats of file '" << absolutePath << "'" << log::endm;
		return Optional<struct stat>();
	}

	return Optional<struct stat>(s);
}