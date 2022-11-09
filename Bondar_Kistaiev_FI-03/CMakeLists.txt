cmake_minimum_required(VERSION 3.8)

#Alias
set(This Lab_AAF_Bondar_Kistaiev)

#Set language
project(${This} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(Headers 
    DataBase/DataBase.hpp
    Parser/Parser.hpp
    SystemControl/SystemControl.hpp
    Node/Node.hpp
)

set(Sources 
    main.cpp
    DataBase/DataBase.cpp
    Parser/Parser.cpp
    SystemControl/SystemControl.cpp
    Node/Node.cpp
)

add_executable(${This} ${Headers} ${Sources})
