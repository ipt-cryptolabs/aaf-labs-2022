cmake_minimum_required(VERSION 3.23)
project(SetOf2DPoints)

set(CMAKE_CXX_STANDARD 14)

add_executable(SetOf2DPoints
        src/main.cpp
        src/Exception.h
        src/Lexer.cpp
        src/Lexer.h
        src/Token.h
        src/Parser.cpp
        src/Parser.h
        src/CLI.cpp
        src/CLI.h)
