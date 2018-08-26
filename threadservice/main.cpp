#include "micro_service.hpp"
#include <iostream>
#include <fstream>
#include <boost/property_tree/json_parser.hpp>
#include <cpprest/json.h>


int writeFile(std::string);

std::function<std::string(std::string, std::string)> execSqlQuery;

std::pair<std::string, int> postHandler(std::string msg) {


   // std::istringstream strm = iss(msg);
  //  auto  jsonMsg = boost::property_tree::json_parser::read_json(strm);

   //

    web::json::value json = web::json::value::parse(msg);
    //writeFile(json.at(U("type")).as_string());
    std::string type = json.at(U("type")).as_string();
    if (type == "get_posts") {
        std::string thread_id = json.at(U("thread_id")).as_string();
        auto message = execSqlQuery("Admin", "SELECT * FROM posts WHERE ThreadId = "+thread_id);
        //writeFile(message);
    }
    int code = 200;
    return {"ddd", code};
}

int main() {
    microservice::MicroService msvc;
    execSqlQuery = msvc.getExecCallback();
    auto regFunc = msvc.getRegCallback();
    regFunc("POST", postHandler);
    msvc.mainLoop();
}

int writeFile (std::string ss)
{
  std::ofstream myfile;
  myfile.open ("example.txt");
  myfile << ss;
  myfile.close();
  return 0;
}

