cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "zxpaint")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT_NAME} LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake) # Custom findSDL2Image cmake

#### Set up Conan and build dependencies #### https://github.com/conan-io/cmake-conan ##################################
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
            TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_configure(REQUIRES spdlog/1.9.2
        sdl/2.0.16
        GENERATORS cmake cmake_paths cmake_find_package)
conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})
########################################################################################################################

find_package(spdlog REQUIRED)
find_package(SDL2 REQUIRED)

find_package(SDL2_image)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

file(GLOB H_FILES "src/*.h")
file(GLOB CPP_FILES "src/*.cpp")

add_executable(zxpaint ${CPP_FILES} ${H_FILES})

target_link_libraries(zxpaint PRIVATE spdlog::spdlog SDL2::SDL2 ${SDL2_IMAGE_LIBRARY})
