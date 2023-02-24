#include "Context.h"
#include <string>
Context::Context(const char * str)
{
    FILE*  file = std::fopen(str,"r");
	if (!file)
		throw "cant open file";

    VirtualServer temp_server = VirtualServer();
	this->add_server(1080,temp_server);

}


Context::iterator Context::port_begin(){
    return servers.begin();
}
Context::iterator Context::port_end(){
    return servers.end();
}
void Context::add_server( int port, VirtualServer& serv){
    servers[port].push_back(serv);
}
const std::vector<VirtualServer>& Context::get_servers_by_port(int port) const {
    return servers.at(port);
}