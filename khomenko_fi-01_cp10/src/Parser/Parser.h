#ifndef AAF_LABS_2022_PARSER_H
#define AAF_LABS_2022_PARSER_H


#include "../Lexer/Lexer.h"
#include "ASTNode.h"
#include "CommandNode.h"
#include "IntegerNode.h"
#include "PointNode.h"
#include "SetNameNode.h"

class Parser {
public:
    Parser(Lexer* lexer): lexer_(lexer){
        current_token_ = lexer_->GetNextToken();
    }

    ASTNode* Parse();

private:
    Lexer* lexer_;
    Token* current_token_;

    Token* Eat(TokenType token_type);

    ASTNode* Expr();
    ASTNode* CreateExpr();
    ASTNode* InsertExpr();
    ASTNode* PrintExpr();
    ASTNode* ContainsExpr();
    ASTNode* SearchExpr();
    ASTNode* WhereExpr();
    ASTNode* InsideExpr();
    ASTNode* LeftOfExpr();
    ASTNode* NNExpr();


    void Error(){
        throw Exception("Invalid syntax!");
    }
};

#endif //AAF_LABS_2022_PARSER_H
