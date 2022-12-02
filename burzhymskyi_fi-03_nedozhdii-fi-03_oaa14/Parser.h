#ifndef BURZHYMSKYI_FI_03_NEDOZHDII_FI_03_OAA14_PARSER_H
#define BURZHYMSKYI_FI_03_NEDOZHDII_FI_03_OAA14_PARSER_H

#include <iostream>
#include <regex>
#include <map>
#include "Tree.h"
#include <locale>

namespace
{
    const static std::regex createRegex("^CREATE\\s[A-Z][A-Z0-9_]*$", std::regex_constants::icase);
    const static std::regex insertRegex("^INSERT\\s[A-Z][A-Z0-9_]*\\s\"(.*)\"$", std::regex_constants::icase);
    const static std::regex printRegex("^PRINT_TREE\\s[A-Z][A-Z0-9_]*$", std::regex_constants::icase);
    const static std::regex containsRegex("^CONTAINS\\s[A-Z][A-Z0-9_]*\\s\"(.*)\"$", std::regex_constants::icase);
    const static std::regex searchRegex("^SEARCH\\s[A-Z][A-Z0-9_]*(\\sWHERE\\s((BETWEEN\\s\"(.+)\",\\s\"(.+)\")|(MATCH\\s\"(.+)\")))?(\\sASC|\\sDESC)?$",std::regex_constants::icase);
    const static std::regex patternRegex("[^*]*[*]?",std::regex_constants::icase);
}

class Parser
{
private:
    std::map<std::string, Tree*> treeName;
    std::vector<std::string> tokens;
    void createTokens(std::string);
    std::string combineTokens();
    int match(std::string);
    bool createTree(std::string);
    bool insertTree(std::string, std::string);
    bool printTree(std::string);
    int containsTree(std::string, std::string);
    void searchTree(std::string name,std::string match,std::string from,std::string to,int k);
public:
    Parser(){};
    ~Parser();
    bool insert(std::string);
    static std::string to_lower(std::string s);
};


#endif //BURZHYMSKYI_FI_03_NEDOZHDII_FI_03_OAA14_PARSER_H
