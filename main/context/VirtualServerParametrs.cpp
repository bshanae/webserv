#include "VirtualServerParametrs.hpp"
#include "VirtualServerParametrsBuolder.hpp"
 VirtualServerParametrs::VirtualServerParametrs(VirtualServerParametrsBuolder &A):
    port(A.port),
    name(A.name),
    root(A.root),
    index(A.index),
    error_page(A.error_page),
    client_max_body_size(A.client_max_body_size),
    upload(A.upload),
    cgi_path(A.cgi_path),
    locations(A.locations),
    ip_adress(A.ip_adress){}