#include "Parser.h"

void Parser::Parse() {
    Expr();
}


void Parser::Eat(TokenType token_type) {
/*  Compare the current token type with the passed token
    type and if they match then "eat" the current token
    and assign the next token to the current_token_,
    otherwise raise an exception.
*/

    if(current_token_->get_type() == token_type){
        current_token_ = lexer_->GetNextToken();
    }
    else{
        Error();
    }
}

void Parser::Expr() {
    /* Expression parser.
     *
     * Expr               : (CreateExpr|InsertExpr|PrintExpr|ContainsExpr|SearchExpr)
     * CreateExpr         : kCreate kSetName kSemicolon
     * InsertExpr         : kInsert kSetName kPoint kSemicolon
     * PrintExpr          : kPrintTree kSetName kSemicolon
     * ContainsExpr       : kContains kSetName kPoint kSemicolon
     * SearchExpr         : kSearch kSetName (kSemicolon | WhereExpr)
     * WhereExpr          : kWhere (InsideExpr | LeftOfExpr | NNExpr) kSemicolon
     * InsideExpr         : kInside kPoint kComma kPoint
     * LeftOfExpr         : kLeftOf kInteger
     * NNExpr             : kNN kPoint
    */


    switch (current_token_->get_type()) {
        case kCreate:
            CreateExpr();
            break;

        case kInsert:
            InsertExpr();
            break;

        case kPrintTree:
            PrintExpr();
            break;

        case kContains:
            ContainsExpr();
            break;

        case kSearch:
            SearchExpr();
            break;

        default:
            Error();
    }

    if(current_token_->get_type() != kEOF){
        Error();
    }
}

void Parser::CreateExpr() {
    Eat(kCreate);
    Eat(kSetName);
    Eat(kSemicolon);
}

void Parser::InsertExpr() {
    Eat(kInsert);
    Eat(kSetName);
    Eat(kPoint);
    Eat(kSemicolon);
}

void Parser::PrintExpr() {
    Eat(kPrintTree);
    Eat(kSetName);
    Eat(kSemicolon);
}

void Parser::ContainsExpr() {
    Eat(kContains);
    Eat(kSetName);
    Eat(kPoint);
    Eat(kSemicolon);
}

void Parser::SearchExpr() {
    Eat(kSearch);
    Eat(kSetName);

    if(current_token_->get_type() == kSemicolon){
        Eat(kSemicolon);
    }
    else{
        if(current_token_->get_type() == kWhere){
            WhereExpr();
        }
        else{
            Error();
        }
    }
}

void Parser::WhereExpr() {
    // kWhere (InsideExpr | LeftOfExpr | NNExpr) kSemicolon

    Eat(kWhere);

    switch (current_token_->get_type()) {
        case kInside:
            InsideExpr();
            break;

        case kLeftOf:
            LeftOfExpr();
            break;

        case kNN:
            NNExpr();
            break;

        default:
            Error();
    }

    Eat(kSemicolon);
}

void Parser::InsideExpr() {
    Eat(kInside);
    Eat(kPoint);
    Eat(kComma);
    Eat(kPoint);
}

void Parser::LeftOfExpr() {
    Eat(kLeftOf);
    Eat(kInteger);
}

void Parser::NNExpr() {
    Eat(kNN);
    Eat(kPoint);
}
