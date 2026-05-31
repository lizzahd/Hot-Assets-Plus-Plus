cmake_minimum_required(VERSION 4.1)
project(hot_assets)

set(CMAKE_CXX_STANDARD 23)

add_library(hot_assets STATIC
        hot_assets/AssetManager.cpp
        hot_assets/AssetManager.h
)

find_path(RAYLIB_CPP_INCLUDE_DIRS "raylib-cpp.hpp")
target_include_directories(hot_assets PUBLIC
        ${RAYLIB_CPP_INCLUDE_DIRS}
)

target_include_directories(hot_assets PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(hot_assets PUBLIC
        raylib
)