#include <iostream>
#include "tools/exceptions/SocketException.h"
#include "server/Server.h"
#include "context/project/Project.h"
#include "context/Context.h"
#include <vector>
#include <map>
#include "context/VirtualServer.hpp"
#include "Include_main.hpp"
// Context buildContext()
// {
// 	Config config;

// 	Project project(config);

// 	Context context(config, project);

// 	return context;
// }

int main(int argv,char ** argc)
{
	
	if (argv != 2){
		std::cout << "Incorrect Argument" << std::cout; 
	}
	try
	{
		Context Context_main(argc[1]);

		Server server(Context_main);
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
