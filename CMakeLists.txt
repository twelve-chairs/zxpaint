cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "zxpaint")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT_NAME} LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake) # Custom findSDL2Image cmake
#
##### Set up Conan and build dependencies #### https://github.com/conan-io/cmake-conan ##################################
#if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
#    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
#    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
#            "${CMAKE_BINARY_DIR}/conan.cmake"
#            TLS_VERIFY ON)
#endif()
#
#include(${CMAKE_BINARY_DIR}/conan.cmake)
#
#conan_cmake_configure(REQUIRES
#        spdlog/1.11.0
##        sdl/2.26.1
##                sdl_image/2.0.5
#        GENERATORS CMakeToolchain CMakeDeps)
#
#conan_cmake_autodetect(settings)
#conan_cmake_install(PATH_OR_REFERENCE .
#        BUILD missing
#        REMOTE conancenter
#        SETTINGS ${settings})
#########################################################################################################################

find_package(spdlog REQUIRED)
find_package(SDL2 REQUIRED)

find_package(SDL2_image)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

file(GLOB H_FILES "src/*.h")
file(GLOB CPP_FILES "src/*.cpp")

add_executable(zxpaint ${CPP_FILES} ${H_FILES})

target_link_libraries(zxpaint PRIVATE spdlog::spdlog SDL2::SDL2 ${SDL2_IMAGE_LIBRARY})
