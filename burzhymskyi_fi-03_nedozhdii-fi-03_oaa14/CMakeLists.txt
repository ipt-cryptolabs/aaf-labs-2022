cmake_minimum_required(VERSION 3.21)
project(burzhymskyi_fi_03_nedozhdii_fi_03_oaa14)

add_subdirectory(./googletest-main)
set(LIBRARIES
        gtest
        pthread)

set(CMAKE_CXX_STANDARD 14)

add_executable(burzhymskyi_fi_03_nedozhdii_fi_03_oaa14 main.cpp Tree.cpp Tree.h)

target_link_libraries(burzhymskyi_fi_03_nedozhdii_fi_03_oaa14 gtest gtest_main)