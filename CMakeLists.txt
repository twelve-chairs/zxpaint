cmake_minimum_required(VERSION 3.16)

set(CMAKE_CONFIGURATION_TYPES "Debug;MinSizeRel" CACHE STRING "" FORCE)

project(zxpaint)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED SDL2::SDL2)

set(spdlog_DIR "/home/runner/work/zxpaint/zxpaint/spdlog")
list(APPEND CMAKE_MODULE_PATH "/home/runner/work/zxpaint/zxpaint/spdlog/cmake")
find_package(spdlog REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(zxpaint main.cpp main.h StarFish.cpp StarFish.h common.cpp common.h)

target_link_libraries(zxpaint ${SDL2_LIBRARIES} PRIVATE spdlog::spdlog)
