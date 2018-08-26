cmake_minimum_required(VERSION 3.11)

project(threadservice)

# set(CMAKE_CXX_FLAGS "-std=c++11")
find_package(cpprestsdk REQUIRED)

set(SOURCES main.cpp)

# Add a library with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

# link against the libraries
target_link_libraries( ${PROJECT_NAME}
    PRIVATE cpprestsdk::cpprest
    microservice::base)

