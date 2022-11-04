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
            std::string lower_str = MakeLower(res_string);

            // CREATE
            if(lower_str == "create"){
                return new Token(kCreate, "Create");
            }

            // INSERT
            if(lower_str == "insert"){
                return new Token(kInsert, "Insert");
            }

            // PRINT_TREE
            if(lower_str == "print_tree"){
                return new Token(kPrintTree, "PrintTree");
            }

            // CONTAINS
            if(lower_str == "contains"){
                return new Token(kContains, "Contains");
            }

            // SEARCH
            if(lower_str == "search"){
                return new Token(kSearch, "Search");
            }

            // WHERE
            if(lower_str == "where"){
                return new Token(kWhere, "Where");
            }

            // INSIDE
            if(lower_str == "inside"){
                return new Token(kInside, "Inside");
            }

            // LEFT_OF
            if(lower_str == "left_of"){
                return new Token(kLeftOf, "LeftOf");
            }

            // NN
            if(lower_str == "nn"){
                return new Token(kNN, "NN");
            }

            // set_name
            std::cmatch result;
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

        if(current_char_ == '-' || isdigit(current_char_)){
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
    bool negative = false;

    std::string res_string;
    if(current_char_ == '-'){
        negative = true;
        Advance();
    }

    while(current_char_ != '\0' && isdigit(current_char_)){
        res_string += current_char_;
        Advance();
    }

    if(negative){
        return -std::stoi(res_string);
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

bool Lexer::IsWhitespaceCharacter(char el) {
    std::vector<char> kWhitespaceCharacters = {' ', '\t', '\r', '\n'};
    return std::find(kWhitespaceCharacters.begin(), kWhitespaceCharacters.end(),el) !=kWhitespaceCharacters.end();
}

std::string Lexer::ClearWhitespaceCharacters(const std::string& str) {
    std::string res_str;
    for(auto el:str){
        if(!IsWhitespaceCharacter(el)){
            res_str += el;
        }
    }
    return res_str;
}

std::string Lexer::MakeLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return str;
}