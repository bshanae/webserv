#pragma once
#include <string>
#include <vector>
#include "Location.hpp"
class VirtualServerParametrsBuolder{
    private:
    std::string::iterator set_init_ip(std::string str);
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
        VirtualServerParametrsBuolder();
        void parse_string(std::string &str,FILE*  file);
        void set_port_and_ip(std::string& );
        void set_name(std::string& );
        void set_root(std::string& );
        void set_index(std::string& );
        void set_err_page(std::string& );
        void set_max_body_size(std::string& );
        void set_upload(std::string& );
        void set_cgi_path(std::string& );

};

