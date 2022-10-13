#include "DB_terminal.h"

DB_terminal::DB_terminal(){
    std::cout << "Init DB terminall..." << std::endl;
}

void DB_terminal::start(){
    nextCommand();
}

std::string DB_terminal::nextCommand(){
    std::cout << ">>";

    std::string command = "";
    getline(std::cin, command,';');

    return command.append(";");
}


Token::Token(std::string type): type(type){
}

Token::Token(std::string type, std::string value): type(type), value(value){}

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

Token Token::pushValue(char symbol){
    this->value += std::string(1, symbol);

    return *this;
}

std::string toUpperCase(std::string s){
    for(int i = 0; i < s.size(); ++i){
        s.at(i) = toupper(s.at(i));
    }

    return s;
}


Interpreter::Interpreter(){}

Token Interpreter::interpretToken(std::string token){
    if(token == ","){
        return Token(_COMMA_TOKEN_, token);
    }

    if(token == ";"){
        return Token(_EOC_TOKEN_, token);
    }

    if(token == "("){
        return Token(_OPEN_BRACKET_TOKEN_, token);
    }

    if(token == ")"){
        return Token(_CLOSE_BRACKET_TOKEN_, token);
    }

    if(token == ">" || token == ">=" || token == "==" || token == "<" || token == "<=" || token == "<>"){
        return Token(_COMPARISON_TOKEN_, token);
    }

    if(isCorrectLiteral(token)){
        for(auto i: COMMAND_TYPES){
            if(toUpperCase(token) == i){
                return Token(_COMMAND_TOKEN_, i);
            }
        }

        return Token(_NAME_TOKEN_, token);
    }

    if(token.at(0) == '"' && token.at(token.size()-1) == '"' && token.size() > 2){
        if(isCorrectLiteral(token.substr(1, token.size()-2))){
            return Token(_VALUE_TOKEN_, token);
        }
    }

    return Token(_UNDEFINED_TOKEN_, token);
}

std::vector<std::string> Interpreter::convertStringCommandToStringVector(std::string str_comm){
    std::vector<std::string> vec_comm;
    std::string temp = "";

    for(int i = 0; i < str_comm.size(); ++i){
        if(str_comm.at(i) == ' '){
            if(temp != ""){
                vec_comm.push_back(temp);
                temp = "";
            }
        }else if(str_comm.at(i) == ',' || str_comm.at(i) == '(' || str_comm.at(i) == ')' || str_comm.at(i) == ';'){
            if(temp != ""){
                vec_comm.push_back(temp);
                temp = "";
            }
            vec_comm.push_back(std::string(1, str_comm.at(i)));
        }else{
            temp += std::string(1, str_comm.at(i));
        }
    }
    
    return vec_comm;
}

std::vector<Token> Interpreter::convertStringVectorCommandToTokenVector(std::vector<std::string> command){
    std::vector<Token> rez_vector;
    for(int i = 0; i < command.size(); ++i){
        rez_vector.push_back(interpretToken(command.at(i)));
    }

    return rez_vector;
}



// std::vector<Token> Interpreter::interpretCommand(std::string command){
//     std::vector<Token> command_t;
    
//     Token cur_token = Token(_EMPTY_TOKEN_);
//     int l = command.size() - 1; // because we don't need to rcognise the last symbol, that is ';'
    
//     try{
//         for(int i = 0; i < l; ++i){
//             if(std::isalpha(command.at(i)) || command.at(i) == '"' || command.at(i) == '_'){ // Do if text
//                 if(cur_token.getValue() == " "){
//                     cur_token.setValue(std::string(1, command.at(i)));
//                 }else{
//                     cur_token.pushValue(command.at(i));
//                 }
//             }
            
//             if(command.at(i) == ' '){ // Do if space
//                 if(cur_token.getValue() != " " && cur_token.getValue() != ""){
//                     interpretToken(cur_token);
//                     command_t.push_back(cur_token);
//                     cur_token = Token(_EMPTY_TOKEN_);
//                 }
//                 cur_token.setValue(" ");
//             }

//             if(command.at(i) == ','){  // Do if comma
//                 interpretToken(cur_token);
//                 command_t.push_back(cur_token);
//                 command_t.push_back(Token(_COMMA_TOKEN_, ","));
//                 cur_token = Token(_EMPTY_TOKEN_);
//                 cur_token.setValue(" ");
//             }

//             if(command.at(i) == '('){ // Do if open bracket
//                 if(cur_token.getValue() != " " && cur_token.getValue() != ""){
//                     interpretToken(cur_token);
//                     cur_token = Token(_EMPTY_TOKEN_);
//                     cur_token.setValue(" ");
//                 }
//                 command_t.push_back(Token(_OPEN_BRACKET_TOKEN_, "("));
//             }
            
//             if(command.at(i) == ')'){ // Do if close bracket
//                 if(cur_token.getValue() != " " && cur_token.getValue() != ""){
//                     interpretToken(cur_token);
//                     cur_token = Token(_EMPTY_TOKEN_);
//                     cur_token.setValue(" ");
//                 }
//                 command_t.push_back(Token(_CLOSE_BRACKET_TOKEN_, ")"));
//             }
//         }
//     }catch(const char *e){
//         std::cerr << e << '\n';
//         throw e;
//     }

//     command_t.push_back(Token(_EOC_TOKEN_, ";"));
//     return command_t;
// }

void printCommand(std::vector<Token> command){
    std::cout << "Command:" << std::endl;
    for(auto i: command){
        std::cout << "\t" << i.getType() << ": " << i.getValue() << std::endl;
    }
    std::cout << "End of command." << std::endl;
}

bool isCorrectLiteral(const char c){
    if(std::isalnum(c) || c == '_'){
        return true;
    }

    return false;
}

bool isCorrectLiteral(std::string s){
    if(std::isdigit(s.at(0))){
        return false;
    }

    bool is_correct_iteral = true;
    for(int i = 0; i < s.size(); ++i){
        if(!isCorrectLiteral(s.at(i))){
            is_correct_iteral = false;
        }
    }

    return is_correct_iteral;
}



