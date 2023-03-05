#include "Context.h"

Context::Context(const Config& config, const Project& project) :
	_config(config),
	_project(project)
{
}

Context::Context(const Context& that) :
	_config(that._config),
	_project(that._project)
{
}

Context& Context::operator=(const Context& that)
{
	_config = that._config;
	_project = that._project;

	return *this;
}

const Config& Context::getConfig() const
{
	return _config;
}

Project& Context::getProject()
{
	return _project;
}