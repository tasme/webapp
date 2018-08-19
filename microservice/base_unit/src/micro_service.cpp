#include <iostream>
#include <usr_interrupt_handler.hpp>
#include <runtime_utils.hpp>
#include <functional>
#include "micro_service.hpp"

#include "sql_driver.hpp"
#include "logic_controller.hpp"
#include "microsvc_controller.hpp"

class microservice::MicroService::Implementation {
public:
    Implementation() : mNetwork(mLogic) {}

    std::map<std::string, std::string> mNetworkSettings;
    std::map<std::string, std::string> mDataSettings;

    sql::SQLDriver mData;
    logic::LogicController mLogic;
    server::MicroserviceController mNetwork;
};

microservice::MicroService::MicroService()
{
    mImpl = new Implementation();
    mImpl->mNetworkSettings = RuntimeUtils::getConfiguration("network_config.cfg");
    mImpl->mDataSettings = RuntimeUtils::getConfiguration("data_config.cfg");
    mImpl->mData.initConnection(mImpl->mDataSettings["db_host"].c_str(),
            mImpl->mDataSettings["db_name"].c_str());
    mImpl->mNetwork.setEndpoint(mImpl->mNetworkSettings["service_endpoint"]);
}

microservice::MicroService::~MicroService()
{

}

std::function<void (std::string, std::function<std::pair<std::string, int> (std::string)>)> microservice::MicroService::getRegCallback()
{
    return [this](std::string name, std::function<std::pair<std::string, int> (std::string)> handler) {
        this->mImpl->mLogic.registerHandler(name,handler);
    };
}

std::function<std::string (std::string, std::string)> microservice::MicroService::getExecCallback()
{
    return [this](std::string connection, std::string query) {
        return this->mImpl->mData.execQuery(connection.c_str(), query.c_str()).toStdString();
    };
}

int microservice::MicroService::mainLoop()
{
    InterruptHandler::hookSIGINT();

    //Start the microservice
    try {
        mImpl->mNetwork.start().wait();
        std::cout << "============================================================================\n"
                  << mImpl->mNetworkSettings["service_name"] << " microservice just started.\n"
                  << "Listening for requests at: " << mImpl->mNetwork.getEndpoint() << '\n'
                  << "============================================================================\n";
        InterruptHandler::waitForUserInterrupt();
        mImpl->mNetwork.stop().wait();
    }
    catch(std::exception & e) {
        std::cerr << "Caught an error: " <<  e.what() << '\n';
        return -1;
    }
    catch(...) {
        RuntimeUtils::printStackTrace();
        return -1;
    }
    return 0;
}
