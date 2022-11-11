#include "Parser.h"

Parser::Parser(std::string str)
{
    createTokens(str);
    str = combineTokens();

    switch (match(str))
    {
        case 0:
            std::cout<< "ERROR INPUT";
            break;
        case 1:
            std::cout<<"create "+tokens[1];
            createTree(tokens[1]);
            break;
        case 2:
            std::cout<<"input "<<tokens[1]<<tokens[2];
            insertTree(tokens[1], tokens[2]);
            break;
        case 3:
            std::cout<<"print "<<tokens[1];
            printTree(tokens[1]);
            break;
        case 4:
            std::cout<<"contains "<<tokens[1];
            break;
        case 5:
            std::cout<<"search "<<tokens[1];
            break;
    }
}

void Parser::createTokens(std::string s)
{
    std::string temp;
    char delims[] = {' ', '\t', '\r', '\n'};
    bool flag = true;
    bool quote = false;
    for (int i = 0; i < s.length(); i++)
    {
        std::string check;
        check = s[i];
        if (s[i] != ' ' && s[i] != '\t' && s[i] != '\r' && s[i] != '\n')
        {
            flag = true;
        }
        else
        {
            flag = false;
        }
        if (s[i] == '\"')
        {
            if (quote == false)
            {
                quote = true;
            }
            else if (quote == true)
            {
                quote = false;
            }
        }
        if (flag == true || quote == true)
        {
            temp += s[i];
        }
        if (temp.length() > 0 && flag == false && quote == false || s.length() - 1 == i)
        {
            tokens.push_back(temp);
            temp = "";
            flag = true;
        }
    }
}

std::string Parser::combineTokens()
{
    std::string res = "";

    for (int i = 0; i < tokens.size(); i++)
    {
        res += tokens[i] + " ";
    }

    return res.substr(0, res.length() - 1);
}

int Parser::match(std::string str)
{
    if(std::regex_match(str,createRegex))
        return 1;
    if(std::regex_match(str,insertRegex))
        return 2;
    if(std::regex_match(str,printRegex) )
        return 3;
    if(std::regex_match(str,containsRegex))
        return 4;
    if(std::regex_match(str,searchRegex))
        return 5;
    return 0;
}

void Parser::createTree(std::string name) {
    Tree* t = new Tree;
    if(treeName.contains(name))
        throw "Tree with such name already exists";

    treeName[name] = &*t;
}

void Parser::insertTree(std::string name, std::string val) {
    if(treeName.contains(name))
        throw "Tree with such name already exists";
    treeName[name]->insert(val);
}

void Parser::printTree(std::string name) {
    if(treeName.contains(name))
        throw "Tree with such name already exists";
    treeName[name]->printTree();
}

