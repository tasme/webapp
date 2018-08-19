cmake_minimum_required(VERSION 3.7)

# Set the project name
project (data)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(Qt5 COMPONENTS Core Sql REQUIRED)

set(SOURCES src/sql_driver.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/)

# Add a library with the above sources
add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(microservice::data ALIAS ${PROJECT_NAME})

# Include the headers
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERS}
    PUBLIC ${Qt5_INCLUDE_DIRECTORIES})

# link against the libraries
target_link_libraries( ${PROJECT_NAME}
    Qt5::Core
    Qt5::Sql)


