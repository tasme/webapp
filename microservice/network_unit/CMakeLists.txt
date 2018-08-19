cmake_minimum_required(VERSION 3.7)

# Set the project name
project (network)

set(CMAKE_CXX_FLAGS "-std=c++17")

# find libraries
find_package(OpenSSL REQUIRED)
find_package(cpprestsdk REQUIRED)


message(OPENSSL_LIBS " ${OPENSSL_LIBRARIES}")

set(SOURCES src/microsvc_controller.cpp
            src/http_server.cpp)

set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add a static library
add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(microservice::network ALIAS ${PROJECT_NAME})

# Include the headers
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERS})

# link against the libraries
target_link_libraries( ${PROJECT_NAME}
    PRIVATE ${OPENSSL_LIBRARIES}
    PRIVATE cpprestsdk::cpprest
    PRIVATE microservice::logic
    PRIVATE microservice::utils)


