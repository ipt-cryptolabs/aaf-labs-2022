#ifndef _DB_TERMINAL_
#define _DB_TERMINAL_
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <map>


class DB_terminal;
class Token;
class Interpreter;

const std::string _TOKEN_ = "TOKEN";
const std::string _VALUE_TOKEN_ = "VALUE";
const std::string _COMMAND_TOKEN_ = "COMMAND";
const std::string _NAME_TOKEN_ = "NAME";
const std::string _OPEN_BRACKET_TOKEN_ = "OPEN BRACKET";
const std::string _CLOSE_BRACKET_TOKEN_ = "CLOSE BRACKET";
const std::string _COMMA_TOKEN_ = "COMMA";
const std::string _COMPARISON_TOKEN_ = "COMPARISON";
const std::string _EOC_TOKEN_ = "EOC";
const std::string _EMPTY_TOKEN_ = "EMPTY";
const std::string _UNDEFINED_TOKEN_ = "UNDEFINED";

std::vector<std::string> COMMAND_TYPES{
    "CREATE",
    "INDEXED",
    "INSERT",
    "INTO",
    "SELECT",
    "FROM",
    "WHERE",
    "ORDER_BY",
    "ASC",
    "DESC",
};


class DB_terminal{
public:
    DB_terminal();
    void start();
    std::string nextCommand();

private:
    // Token current_token = Token(_EMPTY_TOKEN_);  // there is no ined in it yet
    std::vector<Token> current_command;
};

class Token{
public:
    Token(){}
    Token(std::string type);
    Token(std::string type, std::string value);
    std::string getType();
    std::string getValue();
    Token setValue(std::string value);
    Token setType(std::string type);
    Token pushValue(char value);

private:
    std::string type = "";
    std::string value = "";
};

class Interpreter{
public:
    Interpreter();
    Token interpretToken(std::string token);
    std::vector<std::string> convertStringCommandToStringVector(std::string command);
    std::vector<Token> convertStringVectorCommandToTokenVector(std::vector<std::string> command);
    std::vector<std::string> interpretCommand(std::string command);
};

std::string toUpperCase(std::string s);
void printCommand(std::vector<Token> command);
bool isCorrectLiteral(const char c);
bool isCorrectLiteral(std::string s);

#include "DB_terminal.cpp"
#endif