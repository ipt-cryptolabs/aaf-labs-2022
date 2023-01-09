#ifndef AAF_LABS_2022_CLI_H
#define AAF_LABS_2022_CLI_H

#include "iostream"

#include "../Lexer/Lexer.h"
#include "../Parser/Parser.h"
#include "../Interpreter/Interpreter.h"
#include "../DB/DB.h"
#include "../Exception.h"

class SystemControl {
public:
    SystemControl();
    void Run();

private:
    DB* db_;

    void Info();
};



#endif //AAF_LABS_2022_CLI_H
