cmake_minimum_required(VERSION 4.1)
project(hot_assets)

set(CMAKE_CXX_STANDARD 23)

add_library(hot_assets STATIC hot_assets/library.cpp)

target_include_directories(hot_assets PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)