#include "server/Server.h"

int main()
{
	Server server("0:0:0:0", 80);
	server.run();

	return 0;
}
