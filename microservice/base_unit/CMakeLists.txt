cmake_minimum_required (VERSION 3.7)

project(base)

set(CMAKE_CXX_FLAGS "-std=c++17")
set(SOURCES src/micro_service.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create the executable
add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(microservice::base ALIAS ${PROJECT_NAME})

# Include the headers
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERS})

# Link the static libraries from subprojects using it's alias sub::lib
target_link_libraries(${PROJECT_NAME}
    PRIVATE microservice::network
    PRIVATE microservice::logic
    PRIVATE microservice::data
    PRIVATE microservice::utils
)


