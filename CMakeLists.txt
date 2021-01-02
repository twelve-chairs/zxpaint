cmake_minimum_required(VERSION 3.17)
project(SDL2Test)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(SDL2Test main.cpp main.h)

target_link_libraries(SDL2Test ${SDL2_LIBRARIES} nlohmann_json::nlohmann_json)
