#pragma once 

#include <cpprest/http_msg.h>
#include <functional>

#include "http_server.hpp"
#include "logic_controller.hpp"

namespace json =  web::json;
namespace http = web::http;

namespace server {

class MicroserviceController : public HttpServer {
public:
    MicroserviceController(logic::LogicController & logic);
    ~MicroserviceController();
private:
    logic::LogicController & mServiceLogic;

    void intercept(http_request);
    json::value responseNotImpl(const http::method & method);

    virtual void bindRequestInterceptor() override;

};

}
