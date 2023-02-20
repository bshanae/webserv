#include <iostream>
#include "server/Server.h"
#include "exceptions/SocketException.h"

int main()
{
	try
	{
		Server server("0.0.0.0", 80);
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
