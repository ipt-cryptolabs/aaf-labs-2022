#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>

#include "KDtree.hpp"

class ExecManager
{
private:
    std::ostream& os;
    std::istream& is;   
public:
    ExecManager();
    ExecManager(std::ostream& os_, std::istream& is_);
    ~ExecManager();

    void ReadInput();
    std::vector<std::string> Tokenize(std::stringstream& is);
    std::stringstream FineReader();
    
    bool running;
    std::map<std::string, KDtree> vars;
};
