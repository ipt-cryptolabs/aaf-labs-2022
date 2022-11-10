#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include "commands.hpp"
//#include "KDtree.hpp"
#include "exec_manager.hpp"

int main()
{
    std::shared_ptr<Command> comm;
    // std::vector<std::string> a;
    // a = TokenizeInput(std::cin);
    ExecManager exec;
    std::stringstream b;
    Create("t").Execute(exec);
    Insert("t", 1,2).Execute(exec);
    Insert("t", 3,2).Execute(exec);
    Insert("t", -1,2).Execute(exec);
    Insert("t", 2,1).Execute(exec);
    Insert("t", 2,4).Execute(exec);
    PrintTree("t").Execute(exec);
    while (exec.running)
    {
        try
        {
            b = exec.FineReader();
            std::vector<std::string> tokenized = exec.Tokenize(b); 
            comm = RecognizeComm(tokenized);
            comm->Execute(exec);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    
    return 0;
}