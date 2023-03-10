#pragma once

#include <string>
#include <vector>
#include <sys/stat.h>
#include "utils/templates/Optional.h"

class Project
{
	friend std::ostream& operator<<(std::ostream& stream, const Project& project);

public:

	explicit Project(const std::string& root);

	std::string resolvePath(const std::string& relativePath) const;

private:

	std::string _root;
};

std::ostream& operator<<(std::ostream& stream, const Project& project);