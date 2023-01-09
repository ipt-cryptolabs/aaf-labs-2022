cmake_minimum_required(VERSION 3.23)
project(SetOf2DPoints)

set(CMAKE_CXX_STANDARD 17)

set(Headers src/SystemControl/SystemControl.h src/Exception.h  src/Lexer/Lexer.h src/Lexer/Token.h src/Parser/Parser.h src/Parser/ASTNode.h
            src/Parser/CommandNode.h src/Parser/PointNode.h src/Parser/SetNameNode.h src/Parser/IntegerNode.h
            src/Interpreter/Interpreter.h src/Interpreter/NodeVisitor.h src/DB/DB.h src/DB/RTree/RTree.h)

set(Sources src/main.cpp src/SystemControl/SystemControl.cpp src/Lexer/Lexer.cpp src/Parser/Parser.cpp src/Interpreter/Interpreter.cpp
        src/DB/DB.cpp src/DB/RTree/RTree.cpp src/DB/RTree/Rectangle.h src/DB/RTree/Point.h)

add_executable(SetOf2DPoints ${Headers} ${Sources})
