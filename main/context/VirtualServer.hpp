#ifndef VIRTSERV_HPP
#define VIRTSERV_HPP
#include <string>
#include <vector>
#include "Location.hpp"
class VirtualServer{
    private:
        // VirtualServer& operator= (VirtualServer &oth){};
        // VirtualServer(VirtualServer &oth){};
    public:
        int port;
        std::string name;
        std::string root;
        std::string index;
        std::string error_page;
        size_t client_max_body_size;
        std::string upload;
        std::string cgi_path;
        std::vector<location> locations;
        std::string ip_adress;
    public:
        VirtualServer();

};

#endif