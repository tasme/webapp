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
    std::string message;
    web::json::value json = web::json::value::parse(msg);
    //writeFile(json.at(U("type")).as_string());
    std::string type = json.at(U("type")).as_string();
    if (type == "get_posts") {
        std::string thread_id = json.at(U("thread_id")).as_string();
        std::string q = "SELECT * FROM posts WHERE ThreadId="+thread_id;
        writeFile(q);
        message = execSqlQuery("Admin", q);
        web::json::value dbJson = web::json::value::parse(message);
        writeFile(dbJson.at(0).at(U("Text")).as_string());
    } else if (type == "add_post") {
        std::string user_id = json.at(U("user_id")).as_string();
        std::string text = json.at(U("text")).as_string();
        std::string thread_id = json.at(U("thread_id")).as_string();
        message = execSqlQuery("Admin", "INSERT INTO posts (UserId, Text, ThreadId) VALUES ('"+user_id+"', '"+text+"', '"+thread_id+"')");
    }
    int code = 200;
    return {message, code};
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

