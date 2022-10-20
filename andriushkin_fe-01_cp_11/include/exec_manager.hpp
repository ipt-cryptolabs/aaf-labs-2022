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
    std::map<std::string, KDtree> vars;
    std::ostream& os;
    std::istream& is;
    bool running;
public:
    ExecManager();
    ExecManager(std::ostream& os_, std::istream& is_);
    ~ExecManager();

    void ReadInput();
    void RunLoop();
    bool IsRunning();
    std::vector<std::string> Tokenize(std::stringstream& is);
    std::stringstream FineReader();
    
    friend class Command;
    friend class Exit;
    friend class Create;
    friend class Insert;
    friend class Contains;
    friend class PrintTree;
};
