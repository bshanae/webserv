This repo contains implementation of a simple HTTP server. It's a project from 42 Ecole.
Main implementation requirements are following:
* C++ 98
* Non blocking IO
* HTTP/1.1
* GET, POST, DELETE methods
* CGI

## Running

To play around with the server all you have to do is:
```
make
./build/werbserv
```

This command will run example app embedded in this repo.

## Detailed features

### Config

Here is an example of configuration for an app.

```
log {
    info 1
    warning 1
    error 1
    verbose 1
}

media default

server {
    address 0.0.0.0:8080
    root .

    location {
        remote /
        local /www
        methods GET
        index index.html
    }
    
    location {
        remote /cgi-bin
        local /cgi-bin
        methods GET POST
        cgi_enable
    }
}
```

It defines server address and locations.
One for fetching files (pages) with GET requests.
Second for executing scripts.

### Logging

Logs can be tuned in config file.
Several log levels are available.
Logging implementation uses streams, like standard IO.

``` C++
log::i << *this << log::startm << "Staring CGI script at '" << cgiPath << "'" << log::endm;
```

### HTTP

Following method are supported:
* GET
* HEAD
* POST
* PUT
* DELETE

Some feature of requests:
* Support for requests split into multiple TCP segments
* Support for multipart/form-data
* Support for chunked encoding

### CGI

Webserv supports CGI-s in any language.
When invoking CGI script standard request headers are provided to the script, as well as body of the request. 

### Cookies

Webserv support cookies.

P.S. This is quite trivial in terms of implementation...

### Tests

This repo contains two sets of tests.
* One is provided by Ecole 42. It's located at `test/intra`. These tests are quite rigorous. It's ok not to pass them all.
* Second set of tests are my own tests written in Python. They cover many features of the server and can be run automatically, just by command `make test`. They may fail on first run for some reason :) 

## Resources

* [Wiki - HTTP](https://en.wikipedia.org/wiki/HTTP)
* [Building an HTTP Server From Scratch in C++](https://osasazamegbe.medium.com/showing-building-an-http-server-from-scratch-in-c-2da7c0db6cb7)
* [I/O Multiplexing: The select and poll Functions](https://notes.shichao.io/unp/ch6/)
* [Wiki - CGI](https://en.wikipedia.org/wiki/Common_Gateway_Interface)
* [CGI basic](https://lectureswww.readthedocs.io/5.web.server/cgi.html)