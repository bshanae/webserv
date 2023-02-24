#include "VirtualServer.hpp"
#include <cctype>

bool is_all_digit(std::string str,std::string::iterator i)
{
    for(;  i != str.end(); i++ ){
        if (std::isdigit(*i) != true)
            return false;
    }
    return true;
}
std::string::iterator VirtualServer::set_init_ip(std::string str){
    std::string::iterator i = str.begin();
    if (std::atoi(str.c_str()) > 256)
        throw "wrong ip";
    for(int j = 0 ; j  < 3 ; j++){
        if (std::atoi(str.c_str() + (i - str.begin())) > 256)
            throw "wrong ip";
        while(*i != '.' && *i != ':')
            i++;
        if (*i != '.')
            throw "wrong ip";
        i++;
    }
     if (std::atoi(str.c_str() + (i - str.begin())) > 256)
            throw "wrong ip";
        while(*i != '.' && *i != ':')
            i++;
        if (*i != ':')
            throw "wrong ip";
        i++;
        this->ip_adress = str.substr(0, i - str.begin());
        return i;
    
}
VirtualServer::VirtualServer():
    port(1080),
    name(""),
    root("/"),
    index("index.html"),
    error_page("404.html"),
    client_max_body_size(0),
    upload("/upload"),
    cgi_path("/cgi"),
    locations(),
    ip_adress("0.0.0.0")
{}

void VirtualServer::set_port_and_ip(std::string& str){
    std::string::iterator i = str.begin();
    if (str.find(":") == std::string::npos){
        this->ip_adress = "0.0.0.0";
    }
    else{
        if (is_all_digit(str,str.begin()) == false )
            throw "wrong port number";
        i = this->set_init_ip(str);    
    }
    if (is_all_digit(str,i) == false )
            throw "wrong port number";
    int temp_port = std::atoi(str.c_str() + (i - str.begin()));
    if (temp_port <= 0 && temp_port > 65535 )
        throw "wrong port number";
    this->port = temp_port;

}
void VirtualServer::set_root(std::string& str)
{
    this->root = str;
}
void VirtualServer::set_index(std::string& str){
     this->index = str;
}
void VirtualServer::set_err_page(std::string& str){
    this->error_page = str;
}
void VirtualServer::set_max_body_size(std::string& str){
    if (is_all_digit(str,str.begin()) == false )
            throw "wrong max body size";
    this->client_max_body_size = std::atoll(str.c_str());
}
void VirtualServer::set_upload(std::string& str){
    this->upload = str;
}
void VirtualServer::set_cgi_path(std::string& str){
    this->cgi_path = str;
}
void VirtualServer::set_name(std::string& str){
    this->name = str;
}