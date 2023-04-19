#include <fstream>
#include <unistd.h>
#include "config/Config.h"
#include "server/core/CoreServer.h"
#include "server/core/socketControllers/server/ServerSocketController.h"
#include "server/app/Server.h"
#include "log/log.h"
#include "utils/sys/sys.h"
#include "utils/sys/sys.path.h"

using namespace webserv;
using namespace webserv::config;
using namespace webserv::log;

bool getConfigFile(int argc, char** argv, std::string& configPath, std::ifstream& configFile)
{
	if (argc != 2)
	{
		std::cerr << "Invalid usage." << std::endl;
		std::cerr << "Usage: ./webserv [config path]" << std::endl;
		return false;
	}

	configPath = argv[1];

	configFile = std::ifstream(configPath);
	if (!configFile)
	{
		std::cerr << "Can't open file " << configPath << std::endl;
		return false;
	}

	return true;
}

int main(int argc, char** argv)
{
	sys::listenForTermination();

	try
	{
		// read config

		std::string configPath;
		std::ifstream configFile;
		if (!getConfigFile(argc, argv, configPath, configFile))
			return 1;

		Config config;
		configFile >> config;

		// change dir

		char startDir[PATH_MAX];
		if (getcwd(startDir, sizeof(startDir)) == NULL)
			throw std::runtime_error("Can't get current directory");

		const std::string configDir = sys::path::directory(configPath);
		chdir(configDir.c_str());

		// initialize log

		log::initialize(config.log());

		// initialize virtual servers

		std::map<WebAddress, std::vector<Server*> > serversByAddress;
		typedef std::vector<ServerConfig>::const_iterator ServerConfigIterator;
		for (ServerConfigIterator s = config.servers().cbegin(); s != config.servers().cend(); s++)
			serversByAddress[s->address()].push_back(new Server(startDir, *s, config.media()));

		// initialize server socket controllers, link virtual servers to them

		std::vector<ServerSocketController*> serverSockets;
		typedef std::map<WebAddress, std::vector<Server*> >::iterator ServersByAddressIterator;
		for (ServersByAddressIterator sByA = serversByAddress.begin(); sByA != serversByAddress.end(); sByA++)
		{
			serverSockets.push_back(new ServerSocketController(sByA->first));
			for (std::vector<Server*>::iterator s = sByA->second.begin(); s != sByA->second.end(); s++)
				serverSockets.back()->registerDelegate(static_cast<IServerSocketDelegate*>(*s));
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
