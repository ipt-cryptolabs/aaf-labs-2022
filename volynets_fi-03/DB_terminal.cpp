#include "DB_terminal.h"

DB_terminal::DB_terminal(){
    std::cout << "Init DB terminall..." << std::endl;
}

void DB_terminal::start(){
    nextCommand();
}

void DB_terminal::nextCommand(){
    std::cout << ">>";

    Token t = Token(_COMMAND_TOKEN_);
    char c;
    while(t.getValue() != _EOC_TOKEN_){
        cin.get(c);
        if(c == ','){
            for(std::string s: COMMAND_TYPES){
                if(t.getValue())
            }
        }
        
        if(c != ' ' || c != ','){
            t.pushValue(c);
        }
    }
}


Token::Token(std::string type): type(type){
}

std::string Token::getType(){
    return type;
}

std::string Token::getValue(){
    return value;
}

Token Token::setValue(std::string value){
    this->value = value;

    return *this;
}

Token Token::setType(std::string type){
    this->type = type;

    return *this;
}

Token Token::pushValue(std::string symbol){
    this->value += value;

    return *this;
}

std::string toUpperCase(std::string s){
    for(auto c: s){
        c = toupper(c);
    }

    return s;
}
