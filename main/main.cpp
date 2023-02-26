#include <iostream>
#include "tools/exceptions/SocketException.h"
#include "context/ServerStorage.h"
#include "context/project/Project.h"

#include <vector>
#include <map>


// Context buildContext()
// {
// 	Config config;

// 	Project project(config);

// 	Context context(config, project);

// 	return context;
// }

int main(int argv,char ** argc)
{
	
	if (argv != 2)
	{
		std::cout << "Incorrect Argument" << std::endl; 
	}
	try
	{

		ServerStorage server_stor(argc[1]);
		server_stor.print_par();
		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Fatal error: " << exception.what() << std::endl;
		return 1;
	}
	catch (char * str)
	{
		std::cerr << "Fatal error cstring ." << str << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Fatal error." << std::endl;
		return 1;
	}
}
