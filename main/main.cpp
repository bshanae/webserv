#include <iostream>
#include "tools/exceptions/SocketException.h"
#include "server/Server.h"
#include "context/project/Project.h"
#include "context/Context.h"

Context buildContext()
{
	Config config;

	Project project(config);

	Context context(config, project);

	return context;
}

int main()
{
	try
	{
		Context context = buildContext();

		Server server(context);
		server.run();

		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Fatal error: " << exception.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Fatal error." << std::endl;
		return 1;
	}
}
