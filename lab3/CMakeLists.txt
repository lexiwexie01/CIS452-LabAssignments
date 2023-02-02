cmake_minimum_required(VERSION 3.13)  # CMake version check
project(labAssignmentThree)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES labAssignmentThree.c)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(labAssignmentThree ${SOURCE_FILES})

# Set up sample programs
project(dup2Example)
set(SOURCE_FILES ./sample_programs/dup2Example.c)
add_executable(dup2Example ${SOURCE_FILES})

project(fileIOProblem)
set(SOURCE_FILES ./sample_programs/fileIOProblem.c)
add_executable(fileIOProblem ${SOURCE_FILES})

project(sampleProgramOne)
set(SOURCE_FILES ./sample_programs/sampleProgramOne.c)
add_executable(sampleProgramOne ${SOURCE_FILES})

project(sampleProgramTwo)
set(SOURCE_FILES ./sample_programs/sampleProgramTwo.c)
add_executable(sampleProgramTwo ${SOURCE_FILES})