#include "DB_terminal.h"

DB_terminal::DB_terminal(){
    database = Database();
    interpreter = Interpreter(database);
}

void DB_terminal::start(){
    std::cout << "Please, type your comands gently" << std::endl;
    std::string curent_command = "";
    while(true){
        curent_command = nextCommand();
        if(curent_command.substr(0, 4) == "exit"){
            return;
        }
        
        std::cout << interpreter.interpretCommand(curent_command) << std::endl;
    }
}

std::string DB_terminal::nextCommand(){
    std::cout << ">>> ";

    std::string command = "";
    std::cin >> std::ws;

    getline(std::cin, command,';');

    return command.append(";");
}

std::string DB_terminal::callCommand(std::string command){
    return interpreter.interpretCommand(command);
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


Interpreter::Interpreter(){
    database = Database();
}

Interpreter::Interpreter(Database d):database(d){}



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

    if(isCorrectLiteral(token) && !std::isdigit(token.at(0))){
        for(auto i: COMMAND_TYPES){
            if(toUpperCase(token) == i){
                return Token(_COMMAND_TOKEN_, toUpperCase(i));
            }
        }

        return Token(_NAME_TOKEN_, token);
    }

    if(token.at(0) == '"' && token.at(token.size()-1) == '"' && token.size() > 2){
        // if(isCorrectLiteral(token.substr(1, token.size()-2))){
            return Token(_VALUE_TOKEN_, token);
        // }
    }

    return Token(_UNDEFINED_TOKEN_, token);
}

std::vector<std::string> Interpreter::convertStringCommandToStringVector(std::string str_comm){
    std::vector<std::string> vec_comm;
    std::string temp = "";
    bool is_a_string_literal = false;

    for(int i = 0; i < str_comm.size(); ++i){
        if(is_a_string_literal){
            if(str_comm.at(i) == '"'){
                is_a_string_literal = false;
            }
            
            temp += str_comm.at(i);
        }else if(str_comm.at(i) == ' ' || str_comm.at(i) == '\n'){
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
        }else if(str_comm.at(i) == '"'){
            if(temp != ""){
                vec_comm.push_back(temp);
            }
            is_a_string_literal = true;
            temp = "\"";
        }else{
            temp += std::string(1, str_comm.at(i));
        }
    }

    // for(auto i: vec_comm){
    //     std::cout << i << " : ";
    // }
    // std::cout << std::endl;
    
    return vec_comm;
}

std::vector<Token> Interpreter::convertStringVectorCommandToTokenVector(std::vector<std::string> command){
    std::vector<Token> rez_vector;
    for(int i = 0; i < command.size(); ++i){
        rez_vector.push_back(interpretToken(command.at(i)));
    }

    return rez_vector;
}

std::string Interpreter::interpretCommand(std::string command){
    std::vector<Token> token_command = convertStringVectorCommandToTokenVector(
                convertStringCommandToStringVector(command));

    // printCommand(token_command);

    if(token_command.at(0).getValue() == "CREATE"){
        return callCreateCommand(token_command);
    }else if(token_command.at(0).getValue() == "INSERT"){
        return callInsertCommand(token_command);
    }else if(token_command.at(0).getValue() == "SELECT"){
        return callSelectCommand(token_command);
    }else{
        std::cerr << BOLDRED << "Error unknown command: " << token_command.at(0).getValue() << RESET << std::endl;
    }

    return "ERROR: on command: " + token_command.at(0).getValue();
}

std::string Interpreter::callCreateCommand(std::vector<Token> command){
    int i = 0;
    std::string table_name = "";
    std::vector<std::string> table_column_names;
    std::vector<std::string> table_indexed_column_names;

    if(command.at(i).getValue() != "CREATE"){
        std::cerr << BOLDRED<< "Error: unknown command: " << command.at(i).getValue() << RESET << std::endl;
        return "ERROR";
    }
    ++i;

    if(command.at(i).getType() != _NAME_TOKEN_){
        std::cerr << BOLDRED<< "Error: bad name." << command.at(i).getValue() << RESET << std::endl;
        return "ERROR";
    }
    table_name = command.at(i).getValue();
    ++i;

    if(command.at(i).getType() != _OPEN_BRACKET_TOKEN_){
        std::cerr << BOLDRED<< "Error: no open bracket." << RESET << std::endl;
        return "ERROR";
    }
    i++;

    while(command.at(i).getType() != _CLOSE_BRACKET_TOKEN_ && command.at(i).getType() != _EOC_TOKEN_){
        if(command.at(i).getType() == _NAME_TOKEN_){
            table_column_names.push_back(command.at(i).getValue());
        }else{
            std::cerr << BOLDRED<< "Error: mast be a name while get: " << command.at(i).getType() << " that is: " << command.at(i).getValue() << RESET << std::endl;
            return "ERROR";
        }
        ++i;

        if(command.at(i).getValue() == "INDEXED"){
            table_indexed_column_names.push_back(command.at(i-1).getValue());
            ++i;
        }
        

        if(command.at(i).getType() != _COMMA_TOKEN_ && command.at(i).getType() != _CLOSE_BRACKET_TOKEN_){
            std::cerr << BOLDRED<< "Error: unnown type of:" << command.at(i).getType() << " wit walue: " << command.at(i).getValue() << RESET << std::endl;
            return "ERROR";
        }
        ++i;
    }

    if(command.at(i).getType() != _EOC_TOKEN_){
        std::cerr << BOLDRED<< "Error: end of command error." << RESET << std::endl;
        return "ERROR";
    }

    return database.createTable(table_name, table_column_names, table_indexed_column_names);
}

std::string Interpreter::callInsertCommand(std::vector<Token> command){
    int i = 0;
    std::string table_name = "";
    std::vector<std::string> table_column_names;

    if(command.at(i).getValue() != "INSERT"){
        std::cerr << BOLDRED<< "Error: unknown command: " << command.at(i).getValue() << RESET << std::endl;
        return "ERROR";
    }
    ++i;

    if(command.at(i).getValue() == "INTO"){
        ++i;
    }

    if(command.at(i).getType() == _NAME_TOKEN_){
        table_name = command.at(i).getValue();
        ++i;
    }else{
        std::cerr << BOLDRED<< "Error: unknown variable type: " << command.at(i).getType() << " with value: " << command.at(i).getValue() << RESET << std::endl;
        return "ERROR";
    }

    if(command.at(i).getType() != _OPEN_BRACKET_TOKEN_){
        std::cerr << BOLDRED<< "Error: unknown comand syntaxis on open bracket." << RESET << std::endl;
        return "ERROR";
    }
    
    ++i;
    while(command.at(i).getType() != _CLOSE_BRACKET_TOKEN_ && command.at(i).getType() != _EOC_TOKEN_){
        if(command.at(i).getType() == _VALUE_TOKEN_){
            table_column_names.push_back(command.at(i).getValue());
        }else{
            std::cerr << BOLDRED<< "Error: must be value but get: " << command.at(i).getType() << " with value: " << command.at(i).getValue() << RESET << std::endl;
            return "ERROR";
        }
        ++i;

        if(command.at(i).getType() != _COMMA_TOKEN_ && command.at(i).getType() != _CLOSE_BRACKET_TOKEN_){
            std::cerr << BOLDRED<< "Error: must be comma but get: " << command.at(i).getType() << " with value: " << command.at(i).getValue() << RESET << std::endl;
            return "ERROR";
        }
        ++i;

    }

    if(command.at(i).getType() != _EOC_TOKEN_){
        std::cerr << BOLDRED<< "Error: end of command error" << RESET << std::endl;
        return "ERROR";
    }

    for(int i = 0; i < table_column_names.size(); ++i){
        table_column_names.at(i) = table_column_names.at(i).substr(1, table_column_names.at(i).size()-2);
    }

    return database.insert(table_name, table_column_names);
}

std::string Interpreter::callSelectCommand(std::vector<Token> command){
    int i = 0;
    std::string table_name = "", l_value = "", condition = "", r_value = "";
    std::vector<std::pair<std::string, std::string>> order_column_and_type;

    if(command.at(i).getValue() != "SELECT"){
        return "ERROR: command " + command.at(i).getValue() + " is unknown";
    }
    ++i;

    if(command.at(i).getValue() != "FROM"){
        return "ERROR: command " + command.at(i).getValue() + " is unknown";;
    }
    ++i;

    if(command.at(i).getType() == _NAME_TOKEN_){
        table_name = command.at(i).getValue();
        ++i;
    }else{
        std::cerr << BOLDRED<< "Error: unknown variable type." << RESET << std::endl;
        return "ERROR: variable type " + command.at(i).getType() + " is unknown.";
    }

    if(command.at(i).getValue() == "WHERE"){
        i++;
        if(command.at(i).getType() != _NAME_TOKEN_){
            std::cerr << BOLDRED<< "Error: unknown variable type." << RESET << std::endl;
            return "ERROR\n";
        }

        l_value = command.at(i).getValue();
        ++i;

        if(command.at(i).getType() != _COMPARISON_TOKEN_){
            std::cerr << BOLDRED<< "Error: unknown variable type." << RESET << std::endl;
            return "ERROR\n";
        }

        condition = command.at(i).getValue();
        ++i;

        if(command.at(i).getType() != _NAME_TOKEN_ && command.at(i).getType() != _VALUE_TOKEN_){
            std::cerr << BOLDRED<< "Error: unknown variable type." << RESET << std::endl;
            return "ERROR\n";
        }

        r_value = command.at(i).getValue();
        ++i;
    }

    if(command.at(i).getValue() == "ORDER_BY"){
        ++i;
        while(command.at(i).getType() != _EOC_TOKEN_){
            if(command.at(i).getType() != _NAME_TOKEN_){
                return "Error: bad orrder column name";
            }

            ++i;
            
            if(command.at(i).getValue() == "ASC"){
                order_column_and_type.push_back(std::pair(command.at(i-1).getValue(), "ASC"));
                ++i;
            }else if(command.at(i).getValue() == "DESC"){
                order_column_and_type.push_back(std::pair(command.at(i-1).getValue(), "DESC"));
                ++i;
            }

            if(command.at(i).getType() == _COMMA_TOKEN_){
                ++i;
            }
        }
    }

    return database.select(table_name, l_value, condition, r_value, order_column_and_type);
    return "ERROR\n";
}


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
    bool is_correct_iteral = true;
    for(int i = 0; i < s.size(); ++i){
        if(!isCorrectLiteral(s.at(i))){
            is_correct_iteral = false;
        }
    }

    return is_correct_iteral;
}



