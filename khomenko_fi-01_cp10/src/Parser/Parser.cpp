#include "Parser.h"

ASTNode* Parser::Parse() {
    return Expr();
}


Token* Parser::Eat(TokenType token_type) {
/*  Compare the current token type with the passed token
    type and if they match then "eat" the current token,
    return this token and assign the next token to the current_token_,
    otherwise raise an exception.
*/

    if(current_token_->get_type() == token_type){
        Token* token = current_token_;
        current_token_ = lexer_->GetNextToken();
        return token;
    }
    else{
        Error();
    }
    return nullptr;
}

ASTNode* Parser::Expr() {
    /* Expression parser. Return abstract syntax tree as a result of parsing
     *
     * Expr               : (CreateExpr|InsertExpr|PrintExpr|ContainsExpr|SearchExpr) kSemicolon
     * CreateExpr         : kCreate kSetName
     * InsertExpr         : kInsert kSetName kPoint
     * PrintExpr          : kPrintTree kSetName
     * ContainsExpr       : kContains kSetName kPoint
     * SearchExpr         : kSearch kSetName (WhereExpr)
     * WhereExpr          : kWhere (InsideExpr | LeftOfExpr | NNExpr)
     * InsideExpr         : kInside kPoint kComma kPoint
     * LeftOfExpr         : kLeftOf kInteger
     * NNExpr             : kNN kPoint
    */

    ASTNode* root;

    switch (current_token_->get_type()) {
        case kCreate:
            root = CreateExpr();
            break;

        case kInsert:
            root = InsertExpr();
            break;

        case kPrintTree:
            root = PrintExpr();
            break;

        case kContains:
            root = ContainsExpr();
            break;

        case kSearch:
            root = SearchExpr();
            break;

        default:
            root = nullptr;
            Error();
    }

    Eat(kSemicolon);
    if(current_token_->get_type() != kEOF){
        Error();
    }

    return root;
}

ASTNode* Parser::CreateExpr() {
    Token* create_token =  Eat(kCreate);
    Token* set_token = Eat(kSetName);
    return new CommandNode(create_token, new SetNameNode(set_token), nullptr);
}

ASTNode* Parser::InsertExpr() {
    Token* insert_token = Eat(kInsert);
    Token* set_token = Eat(kSetName);
    Token* point_token = Eat(kPoint);
    return new CommandNode(insert_token, new SetNameNode(set_token), new PointNode(point_token));
}

ASTNode* Parser::PrintExpr() {
    Token* print_token = Eat(kPrintTree);
    Token* set_token = Eat(kSetName);
    return new CommandNode(print_token, new SetNameNode(set_token), nullptr);
}

ASTNode* Parser::ContainsExpr() {
    Token* contains_token = Eat(kContains);
    Token* set_token = Eat(kSetName);
    Token* point_token = Eat(kPoint);
    return new CommandNode(contains_token, new SetNameNode(set_token), new PointNode(point_token));
}

ASTNode* Parser::SearchExpr() {
    Token* search_token = Eat(kSearch);
    Token* set_token = Eat(kSetName);

    if(current_token_->get_type() == kSemicolon){
        return new CommandNode(search_token, new SetNameNode(set_token), nullptr);
    }
    else{
        if(current_token_->get_type() == kWhere){
            return new CommandNode(search_token, new SetNameNode(set_token), WhereExpr());
        }
        else{
            Error();
        }
    }
    return nullptr;
}

ASTNode* Parser::WhereExpr() {
    // kWhere (InsideExpr | LeftOfExpr | NNExpr)

    ASTNode* node;
    Token* where_token = Eat(kWhere);

    switch (current_token_->get_type()) {
        case kInside:
            node = InsideExpr();
            break;

        case kLeftOf:
            node = LeftOfExpr();
            break;

        case kNN:
            node = NNExpr();
            break;

        default:
            node = nullptr;
            Error();
    }
    return new CommandNode(where_token, node, nullptr);
}

ASTNode* Parser::InsideExpr() {
    Token* inside_token = Eat(kInside);
    Token* point1_token = Eat(kPoint);
    Eat(kComma);
    Token* point2_token = Eat(kPoint);
    return new CommandNode(inside_token, new PointNode(point1_token), new PointNode(point2_token));
}

ASTNode* Parser::LeftOfExpr() {
    Token* left_of_token = Eat(kLeftOf);
    Token* integer_token = Eat(kInteger);
    return new CommandNode(left_of_token, new IntegerNode(integer_token), nullptr);
}

ASTNode* Parser::NNExpr() {
    Token* nn_token = Eat(kNN);
    Token* point_token = Eat(kPoint);
    return new CommandNode(nn_token, new PointNode(point_token), nullptr);
}
