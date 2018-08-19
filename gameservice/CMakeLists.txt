cmake_minimum_required(VERSION 3.7 )

project(gameservice)

set(CMAKE_CXX_FLAGS "-std=c++11")

set(SOURCES src/main.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add a library with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

# Include the headers
target_include_directories(${PROJECT_NAME}
    PUBLIC ${HEADERS})

# link against the libraries
target_link_libraries( ${PROJECT_NAME}
    microservice::base)
