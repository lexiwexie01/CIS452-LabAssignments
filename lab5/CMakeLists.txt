cmake_minimum_required(VERSION 3.13)  # CMake version check
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

project(Reader)
set(SOURCE_FILES reader.c)
add_executable(Reader ${SOURCE_FILES})

project(Writer)
set(SOURCE_FILES writer.c)
add_executable(Writer ${SOURCE_FILES})

