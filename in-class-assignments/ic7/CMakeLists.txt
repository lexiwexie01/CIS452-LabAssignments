cmake_minimum_required(VERSION 3.13)  # CMake version check
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

project(ic7-consumer)
set(SOURCE_FILES ic7-consumer.c)
add_executable(ic7-consumer ${SOURCE_FILES})

project(ic7-producer)
set(SOURCE_FILES ic7-producer.c)
add_executable(ic7-producer ${SOURCE_FILES})