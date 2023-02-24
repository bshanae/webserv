#pragma once

#include "config/Config.h"
#include "project/Project.h"
#include "VirtualServer.hpp"
#include <vector>
#include <map>
class Context
{
    public:
        Context(const char *str);
        typedef  std::map<int ,std::vector<VirtualServer> >::iterator iterator;
        iterator port_begin();
        iterator port_end();
	    void add_server( int port,VirtualServer& serv);
	    const std::vector<VirtualServer>& get_servers_by_port(int port) const;


    private:
        Context& operator=(const Context& that);
        Context(const Context& that);
	    std::map<int ,std::vector<VirtualServer> > servers;
};
