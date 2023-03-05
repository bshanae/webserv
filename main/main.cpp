#include "tools/exceptions/SocketException.h"
#include "server/Server.h"
#include "context/project/Project.h"
#include "context/Context.h"
#include "tools/log/log.h"
#include "tools/sys/sys.h"

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
		log::initialize();
		log::v.enabled = true;
		log::i.enabled = true;
		log::w.enabled = true;
		log::e.enabled = true;

		sys::listenForTermination();

		Context context = buildContext();

		Server server(context);
		server.run();

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
