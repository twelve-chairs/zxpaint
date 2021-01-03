cmake_minimum_required(VERSION 3.17)
project(SDL2Test)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SDL2Test main.cpp main.h)

target_link_libraries(SDL2Test ${SDL2_LIBRARIES} nlohmann_json::nlohmann_json Boost::filesystem)
