#ifndef SETOF2DPOINTS_INTEGERNODE_H
#define SETOF2DPOINTS_INTEGERNODE_H


class IntegerNode: public ASTNode {
public:
    IntegerNode(Token *token){
        value_ = std::atoi(token->get_value().c_str());
    }

    int get_value(){
        return value_;
    }

private:
    int value_;
};


#endif //SETOF2DPOINTS_INTEGERNODE_H
