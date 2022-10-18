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
    static DBCommand::Node* parse_command(const std::string&);  // Parses command into syntax tree.

private:

    static breakdown_result process_input(const std::string&);
    static DBCommand::Node* build_tree(const std::vector<std::string>&);

    // Building methods
    static DBCommand::Node* build_ERROR_tree(const std::string&);
    static DBCommand::Node* build_CREATE_tree(const std::vector<std::string>&);
    static DBCommand::Node* build_INSERT_tree(const std::vector<std::string>&);
    static DBCommand::Node* build_SELECT_tree(const std::vector<std::string>&);

    // Utility 
    static void make_lower(std::string&);
};