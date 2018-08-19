#pragma once

#include <map>
#include <functional>

namespace logic {

class LogicController
{
public:
    LogicController();
    ~LogicController();

    void registerHandler(std::string name, std::function<std::pair<std::string, int> (std::string)> handler);
    std::function<std::pair<std::string, int> (std::string)> getHandlerByName(std::string name);

private:
    std::map<std::string, std::function<std::pair<std::string, int> (std::string)>> mHandlerMap;
};

}
