cmake_minimum_required(VERSION 3.16)

set(CMAKE_CONFIGURATION_TYPES "Debug;MinSizeRel" CACHE STRING "" FORCE)

project(zxpaint)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED SDL2::SDL2)

list(APPEND CMAKE_PREFIX_PATH "spdlog")
find_package(spdlog REQUIRED)

##set(spdlog_DIR /home/runner/work/zxpaint/zxpaint/spdlog/build)
##set(spdlog_INCLUDE_DIR /home/runner/work/zxpaint/zxpaint/spdlog/include)
if(NOT EXISTS "${spdlog_DIR}")
  find_path(spdlog_DIR
    NAMES spdlogConfig.cmake
    DOC "spdlog base dir"
    )
endif()

if(NOT EXISTS "${spdlog_INCLUDE_DIR}")
  find_path(spdlog_INCLUDE_DIR
    NAMES spdlog/spdlog.h
    DOC "spdlog library header files"
    )
endif()

include_directories(${SDL2_INCLUDE_DIRS} spdlog_INCLUDE_DIR)

add_executable(zxpaint main.cpp main.h StarFish.cpp StarFish.h common.cpp common.h)

target_link_libraries(zxpaint PRIVATE ${SDL2_LIBRARIES} spdlog::spdlog)
