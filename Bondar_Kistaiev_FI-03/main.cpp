#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <regex>
#include <algorithm>

int main()
{
    std::cout << "> ";
    std::string cmd;
    std::getline(std::cin, cmd, ';');
    std::istringstream to_parse(cmd);
    std::string word;
    std::vector<std::string> tokens;

    while(to_parse)
    {
        char curr = to_parse.peek();
        if(curr == '(' || curr == ')' || curr == ',')
            tokens.push_back(std::to_string(to_parse.get()));
        else if(curr == '\"')
        {
            //TODO zrobyty norm
            to_parse.get();
            std::getline(to_parse, word, '\"');
        }
        else
        {
            to_parse >> word;
            tokens.push_back(word);
            std::transform(word.begin(), word.end(), 
                word.begin(), [](char c) { return std::tolower(c); });

            if (word == "where")
            {
                std::getline(to_parse, word, '\0');
                tokens.push_back(word);
            }
        }
    }

    "([a-zA-Z][a-zA-Z0-9_]* | "?*")"

    std::cout << tokens[0] << std::endl;
    // std::regex validation("[a-zA-Z]+ [a-zA-Z]");

    int x;
    std::cin >> x;
}