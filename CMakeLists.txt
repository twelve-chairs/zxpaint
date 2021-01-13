cmake_minimum_required(VERSION 3.17)
project(zxpaint)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED SDL2::SDL2)
find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(zxpaint main.cpp main.h StarFish.cpp StarFish.h common.cpp common.h)

target_link_libraries(zxpaint SDL2::SDL2 spdlog::spdlog nlohmann_json::nlohmann_json)
