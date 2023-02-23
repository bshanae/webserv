#include "Project.h"

#include <fstream>
#include <sstream>
#include "tools/log/log.h"

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

std::string Project::readFile(const std::string& path)
{
	if (path.length() == 0)
	{
		log::e << log::entity << "Project" << log::endl
			   << "Path is empty!" << log::endm;
		return "";
	}

	std::string finalPath = _root;
	if (path[0] != '/')
		finalPath += '/';
	finalPath += path;

	std::ifstream file(finalPath);
	if (!file)
	{
		log::e << log::entity << "Project" << log::endl
			   << "Can't open file at " << finalPath << log::endm;

		return "";
	}

	std::stringstream stream;
	stream << file.rdbuf();

	return stream.str();
}