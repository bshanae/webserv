#pragma once

#include "config/Config.h"
#include "project/Project.h"
#include "VirtualServerParametrs.hpp"
#include "VirtualServerParametrsBuolder.hpp"
#include <vector>
#include <map>
class ServerStorage
{
    public:
        ServerStorage(const char *str);
        typedef  std::vector<VirtualServerParametrs>::iterator iterator;
	    void add_server( VirtualServerParametrsBuolder serv);
	    const std::vector<VirtualServerParametrs>& get_servers() const;
        void print_par();

    private:
        VirtualServerParametrsBuolder parse_server(FILE*  file);
        ServerStorage& operator=(const ServerStorage& that);
        ServerStorage(const ServerStorage& that);

	    std::vector<VirtualServerParametrs> servers;
};
