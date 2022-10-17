#pragma once

#include "..\\Node\\Node.hpp"

// Comentar 
#include <string>
#include <vector>


typedef std::pair<std::vector<std::string>, bool> breakdown_result;
typedef std::pair<DBCommand::Node*, bool> parse_result;

/**
 * Parser Class which provides Syntax and Lexical analysis.
 * 
 * Operates over input string and returns a Node pointer  
 * which represents a syntax tree for a patricular command.
 */
class Parser
{

public:
    static DBCommand::Node* parse_command(std::string);  // Parses command into syntax tree.

private:

    static breakdown_result process_input(std::string);
    static DBCommand::Node* build_tree();
};