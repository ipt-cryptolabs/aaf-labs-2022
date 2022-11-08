cmake_minimum_required(VERSION 3.23)
project(churikov_fi_01)

set(CMAKE_CXX_STANDARD 20)

add_executable(churikov_fi_01 main.cpp Program.cpp Program.hpp Parser.cpp Parser.hpp Request.hpp Storage.cpp Storage.hpp Trie.cpp Trie.hpp)
