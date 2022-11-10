cmake_minimum_required(VERSION 3.24)
project(OAA_lab
    VERSION 1.0
    LANGUAGES CXX)
    
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(lab 
    src/commands.cpp
    src/lab.cpp
    src/exec_manager.cpp
    src/KDtree.cpp)