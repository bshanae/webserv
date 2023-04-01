#include <fstream>
#include <unistd.h>
#include "config/Config.h"
#include "server/core/coreServer/CoreServer.h"
#include "server/core/socketControllers/ServerSocketController.h"
#include "server/app/virtualServer/VirtualServer.h"
#include "log/log.h"
#include "utils/sys/sys.h"
#include "utils/sys/sys.path.h"

using namespace webserv;
using namespace webserv::config;
using namespace webserv::log;

bool getConfigFile(int argc, char** argv, std::ifstream& configFile)
{
	if (argc != 2)
	{
		std::cerr << "Invalid usage." << std::endl;
		std::cerr << "Usage: ./webserv [config path]" << std::endl;
		return false;
	}

	const std::string configPath = argv[1];

	configFile = std::ifstream(configPath);
	if (!configFile)
	{
		std::cerr << "Can't open file " << configPath << std::endl;
		return false;
	}

	const std::string configDir = sys::path::directory(configPath);
	chdir(configDir.c_str());

	return true;
}

int main(int argc, char** argv)
{
	sys::listenForTermination();

	try
	{
		// read config

		std::ifstream configFile;
		if (!getConfigFile(argc, argv, configFile))
			return 1;

		Config config;
		configFile >> config;

		// initialize log

		log::initialize(config.log());

		// initialize virtual servers

		std::map<WebAddress, std::vector<VirtualServer*> > virtualServersByAddress;
		for (std::vector<VirtualServerConfig>::const_iterator vs = config.virtualServers().cbegin(); vs != config.virtualServers().cend(); vs++)
			virtualServersByAddress[vs->address()].push_back(new VirtualServer(*vs, config.media()));

		// initialize server socket controllers, link virtual servers to them

		std::vector<ServerSocketController*> serverSockets;
		for (std::map<WebAddress, std::vector<VirtualServer*> >::iterator aByVs = virtualServersByAddress.begin(); aByVs != virtualServersByAddress.end(); aByVs++)
		{
			serverSockets.push_back(new ServerSocketController(aByVs->first));
			for (std::vector<VirtualServer*>::iterator vs = aByVs->second.begin(); vs != aByVs->second.end(); vs++)
				serverSockets.back()->registerListener(dynamic_cast<IServerSocketListener&>(**vs));
		}

		// run server

		CoreServer server;
		for (int i = 0; i < serverSockets.size(); i++)
			server.registerSocketController(serverSockets[i]);
		server.run();

		// clean up

		for (int i = 0; i < serverSockets.size(); i++)
			delete serverSockets[i];

		for (std::map<WebAddress, std::vector<VirtualServer*> >::iterator aByVs = virtualServersByAddress.begin(); aByVs != virtualServersByAddress.end(); aByVs++)
		{
			for (std::vector<VirtualServer*>::iterator vs = aByVs->second.begin(); vs != aByVs->second.end(); vs++)
				delete *vs;
		}

		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Fatal error: " << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Fatal error." << std::endl;
		return 1;
	}
}
