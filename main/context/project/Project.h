#pragma once

#include <string>
#include <vector>
#include <sys/stat.h>
#include "context/config/Config.h"
#include "tools/templates/Optional.h"

class Project
{
public:

	explicit Project(const Config& config);
	Project(const Project& that);
	Project& operator=(const Project& that);

	struct tm *getTimeOfModification(const std::string& path) const;
	long getSizeInBytes(const std::string& path) const;
	std::string readFile(const std::string& path) const;
	bool isFile(const std::string& path) const;
	bool isDirectory(const std::string& path) const;
	std::vector<std::string> enumerateDirectory(const std::string& path) const;

	friend std::ostream& operator<<(std::ostream& stream, const Project& project);

private:

	std::string _root;

	Optional<struct stat> getStat(const std::string &absolutePath) const;
};

std::ostream& operator<<(std::ostream& stream, const Project& project);