#include "micro_service.hpp"
#include <iostream>
#include <fstream>
#include <boost/property_tree/json_parser.hpp>
#include <cpprest/json.h>


int writeFile(std::string);

std::function<std::string(std::string, std::string)> execSqlQuery;

std::pair<std::string, int> postHandler(std::string msg) {


   //std::istringstream strm = iss(msg);
    //auto  jsonMsg = boost::property_tree::json_parser::read_json(strm);

   //
    std::string message;
    web::json::value json = web::json::value::parse(msg);
    //writeFile(json.at(U("type")).as_string());
    std::string type = json.at(U("type")).as_string();
    if (type == "getPosts") {
        int threadId = json.at(U("threadId")).as_integer();
        std::string q = "SELECT * FROM posts WHERE ThreadId="+std::to_string(threadId);
        //writeFile(q);
        message = execSqlQuery("Regular", q);
        //web::json::value dbJson = web::json::value::parse(message);
        //writeFile(dbJson.at(0).at(U("Text")).as_string());
    } else if (type == "addPost") {
        std::string userId = json.at(U("userId")).as_string();
        std::string text = json.at(U("text")).as_string();
        int  threadId = json.at(U("threadId")).as_integer();
        message = execSqlQuery("Regular", "INSERT INTO posts (UserId, Text, ThreadId) VALUES ('"+userId+"', '"+text+"', "+std::to_string(threadId)+")");
    } else if (type == "getLastThreads") {
        std::cout << "test1\n";
        //message = execSqlQuery("Regular", "SELECT * FROM `threads` ORDER BY `threads`.`Date` DESC LIMIT 100");
        message = execSqlQuery("Regular", "SELECT t.*, (select count(*) from posts p where t.ThreadId = p.ThreadId group by p.ThreadId) as PostCount FROM  threads t ORDER BY t.`Date` DESC LIMIT 100");
        std::cout << "test2\n";
        writeFile(message);
        std::cout << "test3\n";
    } else if (type == "addThread") {
        std::string threadName = json.at(U("threadName")).as_string();
        std::string threadText = json.at(U("threadText")).as_string();
        std::string userId = json.at(U("userId")).as_string();
        int subId = json.at(U("subId")).as_integer();
        message = execSqlQuery("Regular", "INSERT INTO `threads` (`Name`, `Text`, `UserId`, `Date`, `SubId`) VALUES ('"+threadName+"', '"+threadText+"', '"+userId+"', CURRENT_TIMESTAMP, "+std::to_string(subId)+")");
        message = execSqlQuery("Regular", "SELECT LAST_INSERT_ID() as insertedId;");
    } else if (type == "getSubs") {
       // message = execSqlQuery("Regular", "SELECT * FROM `subjects`");
        message="hello world";
    } else if (type == "getThread") {
        int threadId = json.at(U("threadId")).as_integer();
        message = execSqlQuery("Regular", "SELECT * FROM threads WHERE ThreadId="+std::to_string(threadId));
    } else if (type == "getLastThreadsFromSub") {
        int subId = json.at(U("subId")).as_integer();
        int threadAmmount = json.at(U("threadAmmount")).as_integer();
        message = execSqlQuery("Regular", "select t.*, (select count(*) from posts p where t.ThreadId = p.ThreadId group by p.ThreadId) as PostCount from threads t Where t.SubId = "+std::to_string(subId)+" ORDER BY t.Date DESC LIMIT "+std::to_string(threadAmmount));
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

