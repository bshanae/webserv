#pragma once
#include <string>
enum  methods{ GET = 1, POST = 2,DELETE = 4};
class location{
    public:
        std::string uri;
        std::string path;
        std::string redirect;
        char limit_except;
        location();
        void parse_file(FILE*  file);
        void parse_string(std::string & str);
        void set_url(std::string &str);
        void set_path(std::string &str);
        void set_redirect(std::string &str);
        void set_limits(std::string &str);
};
