cmake_minimum_required(VERSION 3.13)  # CMake version check
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

project(ic8)
set(SOURCE_FILES ic8.c)
add_executable(ic8 ${SOURCE_FILES})