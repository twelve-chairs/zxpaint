cmake_minimum_required(VERSION 3.16)

set(CMAKE_CONFIGURATION_TYPES "Debug;MinSizeRel" CACHE STRING "" FORCE)

project(zxpaint)

set(CMAKE_CXX_STANDARD 14)
set(spdlog_DIR /home/runner/work/zxpaint/zxpaint/spdlog)
find_package(SDL2 REQUIRED SDL2::SDL2)

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()
find_package(spdlog REQUIRED HINTS /home/runner/work/zxpaint/zxpaint/spdlog /home/runner/work/zxpaint/zxpaint/spdlog/cmake /home/runner/work/zxpaint/zxpaint/spdlog/build)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(zxpaint main.cpp main.h StarFish.cpp StarFish.h common.cpp common.h)

target_link_libraries(zxpaint ${SDL2_LIBRARIES} PRIVATE spdlog::spdlog)
