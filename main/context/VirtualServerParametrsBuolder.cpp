#include "VirtualServerParametrsBuolder.hpp"
#include <cctype>
#include "tools/exceptions/FileException.hpp"
bool is_all_digit(std::string str,std::string::iterator i)
{
    for(;  i + 1 != str.end() ; i++ ){
        if (*i =='\0')
            return true;
        if (std::isdigit(*i) != true)
            return false;
    }
    return true;
}
void VirtualServerParametrsBuolder::parse_string(std::string &str,FILE*  file){
    size_t i = str.find_first_of(' ');
    if (i == std::string::npos )
    {
        throw FileException("empty parametr");
    }
    std::string name = str.substr(0,i);
    std::string param = str.substr(i);
    size_t trimmed_end = param.find_first_not_of(" ");
    if (trimmed_end != std::string::npos)
        param.erase(0,trimmed_end);
    if (name == "listen")
    {
        this->set_port_and_ip(param);
        return;
    }
    else if (name == "server_name")
    {
        this->set_name(param);
        return;
    }
    else if (name == "root")
    {
        this->set_root(param);
        return;
    }
    else if (name == "index")
    {
        this->set_index(param);
        return;
    }
    else if (name == "error_page")
    {
        this->set_err_page(param);
        return;
    }
    else if (name == "client_max_body_size")
    {
        this->set_max_body_size(param);
        return;
    }
    else if (name == "upload")
    {
        this->set_upload(param);
        return;
    }
    else if (name == "cgi_path")
    {
        this->set_upload(param);
        return;
    }
    else if (name == "location" && param == "{")
    {
        location temp;
        temp.parse_file(file);
        for (std::vector<location>::iterator i = locations.begin(); i != locations.end(); i++)
        {
            if (temp.uri == i->uri)
                throw FileException("locatoin already exist");
        }
        this->locations.push_back(temp);
        return;
    }
    throw FileException("unknown word");

    

}
std::string::iterator VirtualServerParametrsBuolder::set_init_ip(std::string str){
    std::string::iterator i = str.begin();
    if (std::atoi(str.c_str()) > 256)
        throw FileException("wrong ip");
    for(int j = 0 ; j  < 3 ; j++){
        if (std::atoi(str.c_str() + (i - str.begin())) > 256)
            throw FileException("wrong ip");
        while(*i != '.' && *i != ':')
            i++;
        if (*i != '.')
             throw FileException("wrong ip");
        i++;
    }
     if (std::atoi(str.c_str() + (i - str.begin())) > 256)
             throw FileException("wrong ip");
    while(*i != '.' && *i != ':')
            i++;
    if (*i != ':')
         throw FileException("wrong ip");
    
    this->ip_adress = str.substr(0, i - str.begin());
    i++;
    return i;
    
}
VirtualServerParametrsBuolder::VirtualServerParametrsBuolder():
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

void VirtualServerParametrsBuolder::set_port_and_ip(std::string& str){
    std::string::iterator i = str.begin();
    if (str.find(":") == std::string::npos){
        this->ip_adress = "0.0.0.0";
    }
    else{
        i = this->set_init_ip(str);    
    }
    if (is_all_digit(str,i) == false )
            throw FileException("wrong port number");
    int temp_port = std::atoi(str.c_str() + (i - str.begin()));
    if (temp_port <= 0 && temp_port > 65535 )
        throw FileException("wrong port number");
    this->port = temp_port;

}
void VirtualServerParametrsBuolder::set_root(std::string& str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException("wrong root");
    this->root = str;
}
void VirtualServerParametrsBuolder::set_index(std::string& str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException("wrong index");
    this->index = str;
}
void VirtualServerParametrsBuolder::set_err_page(std::string& str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException("wrong err_page");
    this->error_page = str;
}
void VirtualServerParametrsBuolder::set_max_body_size(std::string& str)
{
    if (is_all_digit(str,str.begin()) == false)
        throw FileException( "wrong max body size");
    this->client_max_body_size = std::atoll(str.c_str());
}
void VirtualServerParametrsBuolder::set_upload(std::string& str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException( "wrong upload");
    this->upload = str;
}
void VirtualServerParametrsBuolder::set_cgi_path(std::string& str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException( "wrong cgi_path");
    this->cgi_path = str;
}
void VirtualServerParametrsBuolder::set_name(std::string& str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException( "wrong name");
    
    this->name = str;
}