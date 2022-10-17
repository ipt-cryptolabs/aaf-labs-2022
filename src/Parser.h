#ifndef AAF_LABS_2022_PARSER_H
#define AAF_LABS_2022_PARSER_H


#include "Lexer.h"

class Parser {
public:
    Parser(Lexer* lexer): lexer_(lexer){
        current_token_ = lexer_->GetNextToken();
    }

    void Parse();

private:
    Lexer* lexer_;
    Token* current_token_;

    void Eat(TokenType token_type);

    void Expr();
    void CreateExpr();
    void InsertExpr();
    void PrintExpr();
    void ContainsExpr();
    void SearchExpr();
    void WhereExpr();
    void InsideExpr();
    void LeftOfExpr();
    void NNExpr();



    void Error(){
        throw Exception("Invalid syntax!");
    }
};

#endif //AAF_LABS_2022_PARSER_H
