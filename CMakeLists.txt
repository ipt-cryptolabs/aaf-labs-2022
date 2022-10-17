cmake_minimum_required(VERSION 3.23)
project(SetOf2DPoints)

set(CMAKE_CXX_STANDARD 14)

add_executable(SetOf2DPoints
        src/main.cpp
        src/Exception.h
        src/Lexer/Lexer.cpp
        src/Lexer/Lexer.h
        src/Lexer/Token.h
        src/Parser/Parser.cpp
        src/Parser/Parser.h
        src/CLI/CLI.cpp
        src/CLI/CLI.h)
