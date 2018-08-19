#pragma once

#include <string>
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>

using web::http::experimental::listener::http_listener;
using web::http::http_request;

namespace server {

class HttpServer {
public:
    HttpServer();
    ~HttpServer();

    void setEndpoint(const std::string & value);
    std::string getEndpoint() const;

    pplx::task<void> start();
    pplx::task<void> stop();

    std::vector<utility::string_t> requestPath(const http_request & message);

protected:
    http_listener _listener;

private:
    virtual void bindRequestInterceptor() = 0;
};

}
