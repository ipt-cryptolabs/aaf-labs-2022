#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <regex>
#include <algorithm>
#include "Parser\\Parser.hpp"

int main()
{
    // std::cout << "> ";
    // std::string cmd;
    // std::getline(std::cin, cmd, ';');

    auto mobil = Parser::process_input("abs'sad");

    std::cout << mobil.first[0] << std::endl;

    int x;
    std::cin >> x;
}