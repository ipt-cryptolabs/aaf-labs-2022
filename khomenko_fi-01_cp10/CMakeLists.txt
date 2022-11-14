cmake_minimum_required(VERSION 3.23)
project(SetOf2DPoints)

set(CMAKE_CXX_STANDARD 17)

set(Headers src/CLI/CLI.h src/Exception.h  src/Lexer/Lexer.h src/Lexer/Token.h src/Parser/Parser.h src/Parser/ASTNode.h
            src/Parser/CommandNode.h src/Parser/PointNode.h src/Parser/SetNameNode.h src/Parser/IntegerNode.h
            src/Interpreter/Interpreter.h src/Interpreter/NodeVisitor.h src/DB/DatabaseDAO.h src/DB/DBImpl.h)

set(Sources src/main.cpp src/CLI/CLI.cpp src/Lexer/Lexer.cpp src/Parser/Parser.cpp src/Interpreter/Interpreter.cpp
            src/DB/DBImpl.cpp)

add_executable(SetOf2DPoints ${Headers} ${Sources})
