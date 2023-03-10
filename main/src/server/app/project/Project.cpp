#include "Project.h"

#include <ostream>
#include <string>
#include "utils/sys/sys.path.h"

Project::Project(const std::string& root) : _root(root)
{
}

std::string Project::resolvePath(const std::string& relativePath) const
{
	return sys::path::concat(_root, relativePath);
}

std::ostream& operator<<(std::ostream& stream, const Project& project)
{
	stream << "[Project:root=" << project._root << "]";
	return stream;
}