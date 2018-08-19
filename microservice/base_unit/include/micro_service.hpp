#pragma once
#include<map>
#include<functional>

namespace microservice {

class MicroService
{
public:
    MicroService();
    ~MicroService();

    std::function<void(std::string, std::function<std::pair<std::string, int> (std::string)>)> getRegCallback();
    std::function<std::string(std::string, std::string)> getExecCallback();

    int mainLoop();
private:
    class Implementation;
    Implementation * mImpl;
};

}
