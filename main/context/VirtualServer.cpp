#include "VirtualServer.hpp"
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