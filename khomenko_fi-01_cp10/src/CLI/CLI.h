#ifndef AAF_LABS_2022_CLI_H
#define AAF_LABS_2022_CLI_H

#include "iostream"
#include "../Parser/Parser.h"
#include "../Lexer/Lexer.h"
#include "../Exception.h"

class CLI {
public:
    void Run();

private:
    std::string ProcessInput(std::string input);
    void Info();
};



#endif //AAF_LABS_2022_CLI_H
