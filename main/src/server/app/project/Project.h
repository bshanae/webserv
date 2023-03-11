#pragma once

#include <string>
#include <vector>
#include <sys/stat.h>
#include "utils/templates/Optional.h"

namespace webserv
{
	class Project;
}

std::ostream& operator<<(std::ostream& stream, const webserv::Project& project);

class webserv::Project
{
	friend std::ostream& ::operator<<(std::ostream& stream, const Project& project);

public:

	explicit Project(const std::string& root);

	std::string resolvePath(const std::string& relativePath) const;

private:

	std::string _root;
};