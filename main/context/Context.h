#pragma once

#include "config/Config.h"
#include "project/Project.h"

class Context
{
public:

	Context(const Config& config, const Project& project);

	const Config& getConfig() const;
	Project& getProject();

private:

	Config _config;
	Project _project;
};
