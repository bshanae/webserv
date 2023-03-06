#include "Context.h"

Context::Context(const Config& config, const Project& project) :
	_config(config),
	_project(project)
{
}

const Config& Context::getConfig() const
{
	return _config;
}

Project& Context::getProject()
{
	return _project;
}