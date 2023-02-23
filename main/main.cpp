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
void parse_fail(serv_stor &server_storage)
{
	
	std::vector<VirtualServer> Virt_server;
	Virt_server.push_back(VirtualServer());
	server_storage.insert(serv_stor::value_type(1080,Virt_server));
}
int main()
{
	serv_stor  server_storage;
	try
	{
		parse_fail(server_storage);

		Server server(server_storage);
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
