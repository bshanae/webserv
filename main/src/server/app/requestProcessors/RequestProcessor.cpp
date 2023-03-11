#include "RequestProcessor.h"

using namespace webserv;

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
