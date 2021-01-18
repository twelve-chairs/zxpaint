cmake_minimum_required(VERSION 3.10)

set(CMAKE_CONFIGURATION_TYPES "Debug;MinSizeRel" CACHE STRING "" FORCE)

project(zxpaint)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED SDL2::SDL2)
include_directories(${SDL2_INCLUDE_DIRS})

include(conanbuildinfo.cmake)
conan_basic_setup()

add_executable(zxpaint src/main.cpp src/main.h src/common.cpp src/common.h)

target_link_libraries(zxpaint PUBLIC ${SDL2_LIBRARIES} ${CONAN_LIBS})
