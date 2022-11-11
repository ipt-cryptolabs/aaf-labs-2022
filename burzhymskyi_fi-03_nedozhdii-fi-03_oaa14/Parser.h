#ifndef BURZHYMSKYI_FI_03_NEDOZHDII_FI_03_OAA14_PARSER_H
#define BURZHYMSKYI_FI_03_NEDOZHDII_FI_03_OAA14_PARSER_H

#include <iostream>
#include <regex>
#include <map>
#include "Tree.h"

namespace
{
    const static std::regex createRegex("^CREATE\\s[A-Z][A-Z0-9_]*$", std::regex_constants::icase);
    const static std::regex insertRegex("^INSERT\\s[A-Z][A-Z0-9_]*\\s\"(.*)\"$", std::regex_constants::icase);
    const static std::regex printRegex("^PRINT_TREE\\s[A-Z][A-Z0-9_]*$", std::regex_constants::icase);
    const static std::regex containsRegex("^CONTAINS\\s[A-Z][A-Z0-9_]*\\s\"(.*)\"$", std::regex_constants::icase);
    const static std::regex searchRegex("^SEARCH\\s[A-Z][A-Z0-9_]*(\\sWHERE\\s((BETWEEN\\s\"(.+)\",\\s\"(.+)\")|(MATCH\\s\"(.+)\")))?(\\sASC|\\sDESC)?$",std::regex_constants::icase);
}

class Parser
{
private:
    std::map<std::string, Tree*> treeName;
    std::vector<std::string> tokens;
    void createTokens(std::string);
    std::string combineTokens();
    int match(std::string);
    void createTree(std::string);
    void insertTree(std::string, std::string);
    void printTree(std::string);
    void containsTree(std::string, std::string);
public:
    Parser(std::string);
};


#endif //BURZHYMSKYI_FI_03_NEDOZHDII_FI_03_OAA14_PARSER_H
