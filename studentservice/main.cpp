#include "micro_service.hpp"

std::function<std::string(std::string, std::string)> execSqlQuery;

std::pair<std::string, int> getAllStudents(std::string msg) {
    auto message = execSqlQuery("Admin", "SELECT * FROM students");
    int code = 200;
    return {message, code};
}

int main() {
    microservice::MicroService msvc;
    execSqlQuery = msvc.getExecCallback();
    auto regFunc = msvc.getRegCallback();
    regFunc("GET", getAllStudents);
    msvc.mainLoop();
}
