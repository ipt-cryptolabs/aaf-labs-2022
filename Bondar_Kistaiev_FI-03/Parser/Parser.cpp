#include "Parser.hpp"
#include <sstream>
#include <vector>

DBCommand::Node* Parser::parse_command(std::string cmd)
{
    std::istringstream to_parse(cmd);
    std::string word;
    std::vector<std::string> tokens;

    while(to_parse)
    {
        char curr = to_parse.peek();
        if(curr == '(' || curr == ')')
            tokens.push_back(std::to_string(to_parse.get()));
        else if(curr == ',')
            tokens.push_back(std::to_string(to_parse.get()));
    }
    return nullptr;
} 