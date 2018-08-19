cmake_minimum_required(VERSION 3.7 )

project(studentservice)

set(CMAKE_CXX_FLAGS "-std=c++11")

set(SOURCES main.cpp)

# Add a library with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

# link against the libraries
target_link_libraries( ${PROJECT_NAME}
    microservice::base)
