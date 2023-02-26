#include "Location.hpp"
#include <cctype>
#include "tools/exceptions/FileException.hpp"
void static Trim(std::string& out_line)
{
    size_t trimmed_end = out_line.find_first_of("#");
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

location::location():
        uri(""),
        path("/"),
        redirect(""),
        limit_except(GET & POST & DELETE)
{}
void location::parse_file(FILE*  file)
{
    char bufer[1024];
    while(true){
        fgets(bufer,1024,file);
        std::string str(bufer);
        Trim(str);
        if(str.size() == 0)
            continue;
        if ( str == "}")
            return ;
        this->parse_string(str);
    }
    
}
void location::parse_string(std::string & str)
{
    int i = str.find_first_of(' ');
    std::string name = str.substr(0,i);
    std::string param = str.substr(i);
    size_t trimmed_end = param.find_first_not_of(" ");
    if (trimmed_end != std::string::npos)
        param.erase(0,trimmed_end);
    if (name == "uri")
    {
        set_url(param);
        return;
    }
    else if(name ==  "path")
    {
        set_path(param);
        return;
    }
    else if(name ==  "redirect")
    {
        set_redirect(param);
        return;
    }
    else if(name ==  "limit_except")
    {
        set_limits(param);
        return;
    }
    throw FileException("unknown simvole");

}
void location::set_url(std::string &str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException("wrong url");
    this->uri = str;
}
void location::set_path(std::string &str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException("wrong path");
    this->path = str;
}
void location::set_redirect(std::string &str)
{
    if (str.find_first_of(' ') != std::string::npos)
        throw FileException("wrong redirection");
    this->redirect = str;
}
void location::set_limits(std::string &str)
{
    this->limit_except = 0;
        while (str.size() != 0 )
        {
            size_t trim = str.find_first_of(",");
            std::string temp = str.substr(0,trim);
            if (trim != std::string::npos)
                str.erase(0,trim + 1);
            else 
                str.erase(0,trim);
            if (temp == "GET")
                this->limit_except = this->limit_except | GET;
            else if (temp == "POST")
                this->limit_except = this->limit_except | POST;
            else if (temp == "DELITE")
                this->limit_except = this->limit_except | DELETE;
            else if (temp == "")
                return;
            else
                throw FileException("wrong limits");
        }
        return;
};

