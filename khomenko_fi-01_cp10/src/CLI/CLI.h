#ifndef AAF_LABS_2022_CLI_H
#define AAF_LABS_2022_CLI_H

#include "iostream"

#include "../Lexer/Lexer.h"
#include "../Parser/Parser.h"
#include "../Interpreter/Interpreter.h"
#include "../DB/DBImpl.h"
#include "../Exception.h"

class CLI {
public:
    void Run();

private:
    void Info();
};



#endif //AAF_LABS_2022_CLI_H
