#include <fstream>
#include <unistd.h>
#include "config/Config.h"
#include "server/core/coreServer/CoreServer.h"
#include "server/core/socketControllers/ServerSocketController.h"
#include "server/app/server/Server.h"
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

		std::map<WebAddress, std::vector<Server*> > serversByAddress;
		typedef std::vector<ServerConfig>::const_iterator ServerConfigIterator;
		for (ServerConfigIterator s = config.servers().cbegin(); s != config.servers().cend(); s++)
			serversByAddress[s->address()].push_back(new Server(*s, config.media()));

		// initialize server socket controllers, link virtual servers to them

		std::vector<ServerSocketController*> serverSockets;
		typedef std::map<WebAddress, std::vector<Server*> >::iterator ServersByAddressIterator;
		for (ServersByAddressIterator sByA = serversByAddress.begin(); sByA != serversByAddress.end(); sByA++)
		{
			serverSockets.push_back(new ServerSocketController(sByA->first));
			for (std::vector<Server*>::iterator s = sByA->second.begin(); s != sByA->second.end(); s++)
				serverSockets.back()->registerListener(dynamic_cast<IServerSocketListener&>(**s));
		}

		// run server

		CoreServer server;
		for (int i = 0; i < serverSockets.size(); i++)
			server.registerSocketController(serverSockets[i]);
		server.run();

		// clean up

		for (int i = 0; i < serverSockets.size(); i++)
			delete serverSockets[i];

		for (ServersByAddressIterator sByA = serversByAddress.begin(); sByA != serversByAddress.end(); sByA++)
		{
			for (std::vector<Server*>::iterator s = sByA->second.begin(); s != sByA->second.end(); s++)
				delete *s;
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
