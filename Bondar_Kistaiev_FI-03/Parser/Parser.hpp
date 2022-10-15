#pragma once

#include "..\\Node\\Node.hpp"

/**
 * Parser Class which provides Syntax and Lexical analysis.
 * 
 * Operates over input string and returns a Node pointer  
 * which represents a syntax tree for a patricular command.
 */
class Parser
{

public:
    Node* parse_command(std::string);  // Parses command into syntax tree.


};