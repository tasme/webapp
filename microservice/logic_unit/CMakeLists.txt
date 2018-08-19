cmake_minimum_required(VERSION 3.7)

# Set the project name
project (logic)

set(CMAKE_CXX_FLAGS "-std=c++17")

set(SOURCES src/logic_controller.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add a library with the above sources
add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(microservice::logic ALIAS ${PROJECT_NAME})

# Include the headers
target_include_directories(${PROJECT_NAME}
    PUBLIC ${HEADERS})





