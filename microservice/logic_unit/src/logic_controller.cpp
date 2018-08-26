#include <string>
#include "logic_controller.hpp"



logic::LogicController::LogicController()
{
	
}

logic::LogicController::~LogicController()
{

}

std::function<std::pair<std::string, int> (std::string)> logic::LogicController::getHandlerByName(std::string name)
{
    if(mHandlerMap.find(name) != mHandlerMap.end())
        return mHandlerMap[name];
    else
        return std::function<std::pair<std::string, int> (std::string)>();
}


void logic::LogicController::registerHandler(std::string name, std::function<std::pair<std::string, int> (std::string)> handler)
{
	mHandlerMap[name] = handler;
}


