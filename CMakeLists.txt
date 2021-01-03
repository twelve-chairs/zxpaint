cmake_minimum_required(VERSION 3.17)
project(SDL2Test)

set(CMAKE_CXX_STANDARD 14)
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)

find_package(SDL2 REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED COMPONENTS log)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SDL2Test main.cpp main.h)

target_link_libraries(SDL2Test ${SDL2_LIBRARIES} nlohmann_json::nlohmann_json)
