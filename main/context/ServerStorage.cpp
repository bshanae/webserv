#include "ServerStorage.h"
#include "VirtualServerParametrs.hpp"
#include "VirtualServerParametrsBuolder.hpp"
#include <string>
#include <iostream>
#include "tools/exceptions/FileException.hpp"
void static Trim(std::string& out_line)
{
    size_t trimmed_end = out_line.find_first_of(";#");
    if (trimmed_end != std::string::npos)
        out_line.erase(trimmed_end);
	trimmed_end = out_line.find_first_not_of("\n\t\r ");
	out_line.erase(0, trimmed_end);
	trimmed_end = out_line.find_last_not_of("\n\t\r ");
    if (trimmed_end != std::string::npos)
	{
		out_line.erase(trimmed_end + 1);
	}
    
}

VirtualServerParametrsBuolder ServerStorage::parse_server(FILE*  file)
{
    VirtualServerParametrsBuolder server;
    char bufer[1024];
    while(fgets(bufer,1024,file)){
        std::string str(bufer);
        Trim(str);
        if(str.size() == 0)
            continue;
        if ( str == "}")
            return server;
        server.parse_string(str,file);
    }
    return server;
}
ServerStorage::ServerStorage(const char * file_name)
{
   
    FILE*  file = std::fopen(file_name,"r");
	if (!file){
		throw FileException("cant open file");
    }

    while( ! std::feof(file))
    {
        char bufer[1024];
        fgets(bufer,1024,file);
        std::string str(bufer);
        Trim(str);
        if (str == "")
            continue;
        if ( str == "server {")
            this->add_server(parse_server(file));
    } 

}



void ServerStorage::add_server( VirtualServerParametrsBuolder serv){

    VirtualServerParametrs temp = VirtualServerParametrs(serv);
    for(std::vector<VirtualServerParametrs>:: iterator i = servers.begin();i != servers.end(); i++)
    {
        if (serv.port == i->port && serv.name == i->name)
        {
            throw FileException("Same server already exist");
        }
    }
    servers.push_back(temp);
}
const std::vector< VirtualServerParametrs>& ServerStorage::get_servers() const {
    return servers;
}

void ServerStorage::print_par(){
    for (std::vector<VirtualServerParametrs>::iterator i = servers.begin(); i != servers.end();i++)
    {
        std::cout << "server {\n" 
        << "name " << i->name 
        << "\nport " << i->port
        << "\nip " << i->ip_adress
        << "\nroot " << i->root
        << "\nerror_page " << i->error_page
        << "\nClient_max_body_size " << i->client_max_body_size
        << "\nupload " << i->upload
        << "\ncgi_path " << i->cgi_path;
        for ( std::vector<location>::const_iterator j = i->locations.begin() ; j != i->locations.end() ; j++ )
        {
            std::cout << " location {\n" 
            << " uri " << j->uri 
            << "\n path " << j->path
            << "\n redirect " << j->redirect
            << "\n limit_except " <<  int (j->limit_except)
            << " \n }\n";
        }
        std::cout << "}\n";
    }

}