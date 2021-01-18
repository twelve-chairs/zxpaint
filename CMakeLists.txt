cmake_minimum_required(VERSION 3.16)

set(CMAKE_CONFIGURATION_TYPES "Debug;MinSizeRel" CACHE STRING "" FORCE)

project(zxpaint)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED SDL2::SDL2)

list(APPEND CMAKE_PREFIX_PATH "spdlog")
set(spdlog_DIR /home/runner/work/zxpaint/zxpaint/spdlog/build)
find_package(spdlog REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(zxpaint main.cpp main.h StarFish.cpp StarFish.h common.cpp common.h)

target_link_libraries(zxpaint PRIVATE ${SDL2_LIBRARIES} spdlog::spdlog)
