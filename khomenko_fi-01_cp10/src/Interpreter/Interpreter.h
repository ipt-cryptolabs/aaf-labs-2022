#ifndef SETOF2DPOINTS_INTERPRETER_H
#define SETOF2DPOINTS_INTERPRETER_H


#include "NodeVisitor.h"
#include "../DB/DB.h"

class Interpreter: NodeVisitor {
public:
    Interpreter(Parser* parser, DB* db): parser_(parser), db_(db){   }

    void Interpret();

private:
    Parser* parser_;
    DB* db_;

    void VisitCommand(CommandNode* node) override;
    int VisitInteger(IntegerNode* node) override;
    std::string VisitSetName(SetNameNode* node) override;
    Point* VisitPoint(PointNode* node) override;
};


#endif //SETOF2DPOINTS_INTERPRETER_H
