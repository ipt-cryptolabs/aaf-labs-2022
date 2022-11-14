#ifndef SETOF2DPOINTS_NODEVISITOR_H
#define SETOF2DPOINTS_NODEVISITOR_H

#include <variant>
#include "../Parser/Parser.h"

class NodeVisitor {
public:
    virtual void VisitCommand(CommandNode* node) = 0;
    virtual int VisitInteger(IntegerNode* node) = 0;
    virtual std::string VisitSetName(SetNameNode* node) = 0;
    virtual std::pair<int, int> VisitPoint(PointNode* node) = 0;
};


#endif //SETOF2DPOINTS_NODEVISITOR_H
