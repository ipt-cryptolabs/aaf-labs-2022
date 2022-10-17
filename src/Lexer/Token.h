#ifndef AAF_LABS_2022_TOKEN_H
#define AAF_LABS_2022_TOKEN_H


#include <string>
#include <array>
#include <iostream>
#include <utility>

enum TokenType{ kCreate, kInsert, kPrintTree, kContains, kSearch, kWhere, kInside,
    kLeftOf, kInteger, kNN, kSetName, kPoint, kComma, kSemicolon, kEOF};
const int kTypesAmount = 15;

class Token {
public:
    Token(TokenType type, std::string value): type_(type), value_(std::move(value)){    }

    std::string ToString(){
        return "Token(" + kTokenTypes[type_] + ", " + value_ + ")";
    }

    TokenType get_type(){
        return type_;
    }

    std::string get_value(){
        return value_;
    }

private:
    TokenType type_;
    std::string value_;
    const std::array<std::string, kTypesAmount> kTokenTypes = { "kCreate", "kInsert", "kPrintTree", "kContains",
                                                                "kSearch", "kWhere", "kInside", "kLeftOf", "kInteger",
                                                                "kNN", "kSetName", "kPoint", "kComma", "kSemicolon", "kEOF"};
};

#endif //AAF_LABS_2022_TOKEN_H
