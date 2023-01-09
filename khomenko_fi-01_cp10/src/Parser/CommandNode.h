#ifndef SETOF2DPOINTS_COMMANDNODE_H
#define SETOF2DPOINTS_COMMANDNODE_H


class CommandNode: public ASTNode {
public:
    CommandNode(Token* op, ASTNode* left, ASTNode* right): left_(left), op_(op), right_(right){

    }

    Token* get_op(){
        return op_;
    }

    ASTNode* get_left(){
        return left_;
    }

    ASTNode* get_right(){
        return right_;
    }

private:
    ASTNode* left_;
    Token* op_;
    ASTNode* right_;
};


#endif //SETOF2DPOINTS_COMMANDNODE_H
