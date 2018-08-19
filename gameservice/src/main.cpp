#include "micro_service.hpp"
#include <string>
#include <functional>

std::function<std::string(std::string, std::string)> queryHandler;
std::pair<std::string, int> GETHandler(std::string);

int main()
{
    microservice::MicroService msvc;
    auto regHandler = msvc.getRegCallback();
    queryHandler = msvc.getExecCallback();
    regHandler("GET", GETHandler);
    msvc.mainLoop();
}

std::pair<std::string, int> GETHandler(std::string) {
    //auto json = queryHandler("Regular", "SELECT * FROM table");
    //return json;
    return {"ERROR\n", 404};
}
