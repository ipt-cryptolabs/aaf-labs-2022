#include "Lexer.h"


Token *Lexer::GetNextToken() {
    while(current_char_ != '\0') {
        if(isalpha(current_char_)){
            // Probably command input or set_name

            std::string res_string;
            while(current_char_ != '\0' && (isalnum(current_char_) || current_char_ == '_')){
                res_string += current_char_;
                Advance();
            }

            std::cmatch result;

            // CREATE
            std::regex create_reg("[Cc][Rr][Ee][Aa][Tt][Ee]");
            if(std::regex_match(res_string.c_str(), result, create_reg)){
                return new Token(kCreate, "Create");
            }

            // INSERT
            std::regex insert_reg("[Ii][Nn][Ss][Ee][Rr][Tt]");
            if(std::regex_match(res_string.c_str(), result, insert_reg)){
                return new Token(kInsert, "Insert");
            }

            // PRINT_TREE
            std::regex print_reg("[Pp][Rr][Ii][Nn][Tt]_[Tt][Rr][Ee][Ee]");
            if(std::regex_match(res_string.c_str(), result, print_reg)){
                return new Token(kPrintTree, "PrintTree");
            }

            // CONTAINS
            std::regex contains_reg("[Cc][Oo][Nn][Tt][Aa][Ii][Nn][Ss]");
            if(std::regex_match(res_string.c_str(), result, contains_reg)){
                return new Token(kContains, "Contains");
            }

            // SEARCH
            std::regex search_reg("[Ss][Ee][Aa][Rr][Cc][Hh]");
            if(std::regex_match(res_string.c_str(), result, search_reg)){
                return new Token(kSearch, "Search");
            }

            // WHERE
            std::regex where_reg("[Ww][Hh][Ee][Rr][Ee]");
            if(std::regex_match(res_string.c_str(), result, where_reg)){
                return new Token(kWhere, "Where");
            }

            // INSIDE
            std::regex inside_reg("[Ii][Nn][Ss][Ii][Dd][Ee]");
            if(std::regex_match(res_string.c_str(), result, inside_reg)){
                return new Token(kInside, "Inside");
            }

            // LEFT_OF
            std::regex left_of_reg("[Ll][Ee][Ff][Tt]_[Oo][Ff]");
            if(std::regex_match(res_string.c_str(), result, left_of_reg)){
                return new Token(kLeftOf, "LeftOf");
            }

            // NN
            std::regex nn_reg("[Nn][Nn]");
            if(std::regex_match(res_string.c_str(), result, nn_reg)){
                return new Token(kNN, "NN");
            }

            // set_name
            std::regex set_name_reg("[a-zA-Z][a-zA-Z0-9_]*");
            if(std::regex_match(res_string.c_str(), result, set_name_reg)){
                return new Token(kSetName, res_string);
            }
            Error();
        }

        if(current_char_ == '('){
            // Probably point

            std::string res_string;
            while(current_char_ != '\0'){

                res_string += current_char_;
                if(current_char_ == ')') {
                    Advance();
                    break;
                }

                Advance();
            }

            std::cmatch result;
            std::regex point_reg(R"(\(\s*([+-]?[1-9]\d*|0)\s*,\s*([+-]?[1-9]\d*|0)\s*\))");
            if(std::regex_match(res_string.c_str(), result, point_reg)){
                return new Token(kPoint, ClearWhitespaceCharacters(res_string));
            }
            PointError();
        }

        if(isdigit(current_char_)){
            //probably Integer
            return new Token(kInteger, std::to_string(Integer()));
        }

        if (IsWhitespaceCharacter(current_char_)) {
            Skip();
            continue;
        }

        if (current_char_ == ',') {
            Advance();
            return new Token(kComma, ",");
        }

        if (current_char_ == ';') {
            Advance();
            return new Token(kSemicolon, ";");
        }

        Error();
    }
    return new Token(kEOF, "");
}

int Lexer::Integer() {
    // Return a (multidigit) integer(str) consumed from the input
    std::string res_string;

    while(current_char_ != '\0' && isdigit(current_char_)){
        res_string += current_char_;
        Advance();
    }
    return std::stoi(res_string);
}

void Lexer::Skip() {
    while(current_char_ != '\0' && IsWhitespaceCharacter(current_char_)){
        Advance();
    }
}

void Lexer::Advance() {
    // Updates current_char if pos_ does not exceed text size
    pos_ += 1;

    if(pos_ > text_.size() - 1){
        current_char_ = '\0'; // indicates end of input
    }
    else{
        current_char_ = text_[pos_];
    }
}

std::string Lexer::ClearWhitespaceCharacters(std::string str) {
    std::string res_str;
    for(auto el:str){
        if(!IsWhitespaceCharacter(el)){
            res_str += el;
        }
    }
    return res_str;
}


