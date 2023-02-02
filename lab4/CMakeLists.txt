cmake_minimum_required(VERSION 3.13)  # CMake version check
project(labAssignmentFour)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES labAssignmentFour.c)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(labAssignmentFour ${SOURCE_FILES})

# Set up sample programs
project(sampleProgramOne)
set(SOURCE_FILES sample_programs/sampleProgramOne.c)
add_executable(sampleProgramOne ${SOURCE_FILES})

project(sampleProgramTwo)
set(SOURCE_FILES sample_programs/sampleProgramTwo.c)
add_executable(sampleProgramTwo ${SOURCE_FILES})

project(sampleProgramThree)
set(SOURCE_FILES sample_programs/sampleProgramThree.c)
add_executable(sampleProgramThree ${SOURCE_FILES})

project(test)
set(SOURCE_FILES sample_programs/test.c)
add_executable(test ${SOURCE_FILES})