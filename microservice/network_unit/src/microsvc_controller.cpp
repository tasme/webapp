#define BOOST_SPIRIT_THREADSAFE // enable thread safety to json read on property tree!
#include <boost/property_tree/json_parser.hpp>
#include <pplx/pplxtasks.h>

#include "microsvc_controller.hpp"
#include <string>

using web::http::methods;
using web::http::http_response;
using web::http::status_codes;


void server::MicroserviceController::bindRequestInterceptor() {
    _listener.support(methods::GET, std::bind(&MicroserviceController::intercept, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&MicroserviceController::intercept, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&MicroserviceController::intercept, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&MicroserviceController::intercept, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&MicroserviceController::intercept, this, std::placeholders::_1));
}

server::MicroserviceController::MicroserviceController(logic::LogicController & logic) : mServiceLogic(logic)
{

}

server::MicroserviceController::~MicroserviceController()
{

}

void server::MicroserviceController::intercept(http_request message) {
    http_response response;
    response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
    if (message.method() == methods::POST) {
        auto handler = mServiceLogic.getHandlerByName("POST");
        if (handler) {
            message.
             extract_json().
             then([=](web::json::value msg) {
                auto repl = handler(msg.to_string());

                http_response response;
                response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
                response.set_status_code(repl.second);
                response.set_body(repl.first);
                message.reply(response);
             });
        }
        else {
            response.set_status_code(status_codes::NotImplemented);
            response.set_body(responseNotImpl(message.method()));
            message.reply(response);
        }
    }
}

json::value server::MicroserviceController::responseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response["serviceName"] = json::value::string("News microservice");
    response["answer"] = json::value::string(std::string("The ")
                                             + std::string(method.c_str())
                                             + std::string(" method is not implemented yet."));
    return response ;
}
