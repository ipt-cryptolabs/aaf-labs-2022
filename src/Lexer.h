#ifndef AAF_LABS_2022_LEXER_H
#define AAF_LABS_2022_LEXER_H


#include <regex>
#include <vector>

#include "Token.h"
#include "Exception.h"

class Lexer {
public:
    Lexer(std::string text):text_(std::move(text)), pos_(0) {
        current_char_ = text_[pos_];
    }
    Token* GetNextToken();

private:
    std::string text_;
    int pos_;
    char current_char_;
    std::vector<char> kWhitespaceCharacters = {' ', '\t', '\r', '\n'};


    int Integer();
    void Skip();
    void Advance();

    bool IsWhitespaceCharacter(char el){
        return std::find(kWhitespaceCharacters.begin(), kWhitespaceCharacters.end(),el) != kWhitespaceCharacters.end();
    }
    std::string ClearWhitespaceCharacters(std::string str);

    static void Error(){
        throw Exception("Invalid character!");
    }

    static void PointError(){
        throw Exception("Invalid structure of point!");
    }
};


#endif //AAF_LABS_2022_LEXER_H
