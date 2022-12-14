#include "Parser.h"

Parser::~Parser()
{
    for(auto & [key, value] : treeName)
    {
        delete value;
    }
}

std::string Parser::to_lower(std::string s)
{
    for(char &c : s)
        c = tolower(c);
    return s;
}

bool Parser::insert(std::string str)
{
    tokens.clear();
    createTokens(str);
    str = combineTokens();
    if(tokens[0] == "q:")
    {
        return 0;
    }
    for(int i = tokens.size() - 1; i < 7; ++i)//7 - max size of parsed sentence
        tokens.push_back("");

    switch (match(str))
    {
        case 0:
            std::cout<< "ERROR INPUT" << std::endl;
            break;
        case 1:
            if(createTree(tokens[1]))
              //  std::cout<<"create " + tokens[1] + " done" << std::endl;
            break;
        case 2:

            if(insertTree(tokens[1], tokens[2].substr(1, tokens[2].length()-2)))
               // std::cout << "input: " << tokens[1] << " " << tokens[2] + " done" << std::endl;
            break;
        case 3:
            if(printTree(tokens[1]))
               // std::cout << "print " << tokens[1] + " done" << std::endl;
            break;
        case 4:
        {
            int r = containsTree(tokens[1],tokens[2].substr(1, tokens[2].length()-2));
            if(r >= 0)
                std::cout <<r<< std::endl;
            break;
        }
        case 5:
            if(tokens[3]== "" || tokens[4]=="")
            {
                if(to_lower(tokens[2]) == "desc")
                    searchTree(tokens[1],"","","",1);
                else
                    searchTree(tokens[1],"","","",0);
                break;
            }
            if(to_lower(tokens[3]) == "match")
            {
                std::string parMatch = tokens[4].substr(1, tokens[4].length()-2);
                if(std::regex_match((parMatch),patternRegex))
                {
                    if(to_lower(tokens[5]) == "desc")
                        searchTree(tokens[1],parMatch,"","",1);
                    else
                        searchTree(tokens[1],parMatch,"","",0);
                }
                break;
            }
            //std::cout<<tokens[4].substr(1, tokens[4].length()-3)<<" "+tokens[5].substr(1, tokens[5].length()-2)+"\n";
            if(to_lower(tokens[5]) == "desc")
                searchTree(tokens[1],"",tokens[4].substr(1, tokens[4].length()-3),tokens[5].substr(1, tokens[5].length()-2),1);
            else
                searchTree(tokens[1],"",tokens[4].substr(1, tokens[4].length()-3),tokens[5].substr(1, tokens[5].length()-2),0);

    }
    return 1;
}

void Parser::createTokens(std::string s)
{
    std::string temp;
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
        if ((temp.length() > 0 && flag == false && quote == false) || (s.length() - 1 == i && flag == true))
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

bool Parser::createTree(std::string name) {

    if(treeName.contains(name))
    {
        std::cout << "Tree with such name already exists" << std::endl;
        return 0;
    }
    Tree* t = new Tree;
    treeName[name] = t;
    return 1;
}

bool Parser::insertTree(std::string name, std::string val)
{
    if(!treeName.contains(name))
    {
        std::cout << "Tree with such name doesn't exist" << std::endl;
        return 0;
    }
    treeName[name]->insert(val);
    return 1;
}

bool Parser::printTree(std::string name)
{
    if (!treeName.contains(name))
    {
        std::cout << "Tree with such name doesn't exist" << std::endl;
        return 0;
    }
    treeName[name]->printTree();
    return 1;
}

int Parser::containsTree(std::string name, std::string val)
{
    if (!treeName.contains(name))
    {
        std::cout << "Tree with such name doesn't exist" << std::endl;
        return -1;
    }
    return treeName[name]->contains(val);
}


void Parser::searchTree(std::string name,std::string match,std::string from,std::string to,int k)
{
    if (!treeName.contains(name))
    {
        std::cout << "Tree with such name doesn't exist" << std::endl;
        return;
    }
    treeName[name]->search(match,from,to,k);

}
