#include "http_server.hpp"
#include "network_utils.hpp"

server::HttpServer::HttpServer() {

}

server::HttpServer::~HttpServer() {

}

void server::HttpServer::setEndpoint(const std::string & value) {
    web::uri endpointURI(value);
    web::uri_builder endpointBuilder;

    endpointBuilder.set_scheme(endpointURI.scheme());
    if (endpointURI.host() == "host_auto_ip4") {
        endpointBuilder.set_host(NetworkUtils::hostIP4());
    }
    else if (endpointURI.host() == "host_auto_ip6") {
        endpointBuilder.set_host(NetworkUtils::hostIP6());
    }
    else {
        endpointBuilder.set_host(endpointURI.host());
    }
    endpointBuilder.set_port(endpointURI.port());
    endpointBuilder.set_path(endpointURI.path());

    _listener = http_listener(endpointBuilder.to_uri());
}

std::string server::HttpServer::getEndpoint() const {
    return _listener.uri().to_string();
}

pplx::task<void> server::HttpServer::start() {
    bindRequestInterceptor();
    return _listener.open();
}

pplx::task<void> server::HttpServer::stop() {
    return _listener.close();
}

std::vector<utility::string_t> server::HttpServer::requestPath(const http_request & message) {
    auto relativePath = web::uri::decode(message.relative_uri().path());
    return web::uri::split_path(relativePath);
}
