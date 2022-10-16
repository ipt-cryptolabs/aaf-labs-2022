#include "Parser.hpp"
#include <sstream>
#include <vector>
#include <regex>

DBCommand::Node* Parser::parse_command(std::string cmd)
{
    auto [r, k] = process_input(cmd); // MATLAB moment
    //TODO : Build a tree, grow a house, plant a son.  

    return nullptr;
} 

breakdown_result Parser::process_input(std::string cmd)
{
    std::istringstream to_parse(cmd);
    std::string word;
    std::vector<std::string> tokens;

    const std::regex token_regex("[a-zA-Z][a-zA-Z0-9_]*");
    std::smatch base_match;

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
            tokens.push_back(word);
        }
        else
        {
            to_parse >> word;

            if(!std::regex_match(word, base_match, token_regex))
            {
                tokens.clear();
                tokens.push_back(word + " is not a valid command token.");
                return {tokens, false};
            }

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

    return {tokens, true};
}