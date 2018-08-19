cmake_minimum_required (VERSION 3.7)

project(utils)

find_package(Boost REQUIRED COMPONENTS system)
message(BOOST_LIBS " ${Boost_LIBRARIES}")

set(CMAKE_CXX_FLAGS "-std=c++17")
set(SOURCES src/network_utils.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create the executable
add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(microservice::utils ALIAS ${PROJECT_NAME})

# Include the headers
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERS})

# Link the static libraries from subprojects using it's alias sub::lib
target_link_libraries(${PROJECT_NAME}    
        PRIVATE ${BOOST_LIBRARIES})


