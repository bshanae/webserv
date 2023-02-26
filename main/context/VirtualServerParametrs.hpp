#pragma once
#include <string>
#include <vector>
#include "VirtualServerParametrsBuolder.hpp"
#include "Location.hpp"

class VirtualServerParametrs{
    private:
   // std::string::iterator set_init_ip(std::string str);
        // VirtualServer& operator= (VirtualServer &oth){};
        // VirtualServer(VirtualServer &oth){};
    public:
        const int port;
        const std::string name;
        const std::string root;
        const std::string index;
        const std::string error_page;
        const size_t client_max_body_size;
        const std::string upload;
        const std::string cgi_path;
        const std::vector<location> locations;
        const std::string ip_adress;
    public:
        VirtualServerParametrs(VirtualServerParametrsBuolder &builder);


};