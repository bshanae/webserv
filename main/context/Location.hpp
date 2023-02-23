#ifndef LOCATION_HPP
#define LOCATION_HPP
#include <string>
enum  methods{ GET = 0, POST = 1,DELETE = 2};
class location{
    std::string uri;
    std::string path;
    std::string redirect;
    char limit_except;
    location():
        uri(""),
        path("/"),
        redirect(""),
        limit_except(GET & POST & DELETE)
    {}
};
#endif