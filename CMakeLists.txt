cmake_minimum_required(VERSION 3.10)

set(CMAKE_CONFIGURATION_TYPES "Debug;MinSizeRel" CACHE STRING "" FORCE)

project(zxpaint)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED SDL2::SDL2)

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(zxpaint main.cpp main.h common.cpp common.h)

target_link_libraries(zxpaint PUBLIC ${SDL2_LIBRARIES} spdlog::spdlog)
