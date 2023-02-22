#include "Project.h"

#include <fstream>
#include <sstream>
#include "tools/log/log.h"

Project::Project(const Config &config)
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

std::string Project::readFile(const std::string &path)
{
	const std::string finalPath = _root + "/" + path;

	std::ifstream file(finalPath);
	if (!file)
	{
		log::e << log::entity << "Project" << log::endl;
		log::e << "Can't open file at " << finalPath << log::endm;

		return "";
	}

	std::stringstream stream;
	stream << file.rdbuf();

	return stream.str();
}