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
    ExecManager exec;
    std::stringstream b;
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