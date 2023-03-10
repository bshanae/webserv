#include "config/Config.h"
#include "server/core/coreServer/CoreServer.h"
#include "server/core/socketControllers/ServerSocketController.h"
#include "server/app/virtualServer/VirtualServer.h"
#include "log/log.h"
#include "utils/sys/sys.h"

int main()
{
	sys::listenForTermination();

	try
	{
		// read config

		Config config;

		// initialize log

		log::initialize(config.log());

		// initialize virtual servers

		std::map<WebAddress, std::vector<VirtualServer*> > virtualServersByAddress;
		for (std::vector<VirtualServerConfig>::const_iterator vs = config.virtualServers().cbegin(); vs != config.virtualServers().cend(); vs++)
			virtualServersByAddress[vs->address()].push_back(new VirtualServer(*vs));

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
		log::e << "Fatal error: " << e.what() << log::endm;
		return 1;
	}
	catch (...)
	{
		log::e << "Fatal error." << log::endm;
		return 1;
	}
}
