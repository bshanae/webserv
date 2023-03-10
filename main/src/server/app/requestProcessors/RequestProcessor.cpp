#include "RequestProcessor.h"

RequestProcessor::RequestProcessor(Project& project) : _project(project)
{
}

RequestProcessor::~RequestProcessor()
{
}

Project& RequestProcessor::project()
{
	return _project;
}
