cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "zxpaint")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT_NAME} LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake) # Custom findSDL2Image cmake

find_package(spdlog REQUIRED)
find_package(SDL2 REQUIRED)

find_package(SDL2_image)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

file(GLOB H_FILES "src/*.h")
file(GLOB CPP_FILES "src/*.cpp")

add_executable(zxpaint ${CPP_FILES} ${H_FILES})

target_link_libraries(zxpaint PRIVATE spdlog::spdlog SDL2::SDL2 ${SDL2_IMAGE_LIBRARY})
