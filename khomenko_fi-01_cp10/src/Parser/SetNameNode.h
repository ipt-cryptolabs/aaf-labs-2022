#ifndef SETOF2DPOINTS_SETNAMENODE_H
#define SETOF2DPOINTS_SETNAMENODE_H


class SetNameNode: public ASTNode {
public:
    SetNameNode(Token* set_name): table_name_(set_name->get_value()){

    }

    std::string get_value(){
        return table_name_;
    }

private:
    std::string table_name_;
};


#endif //SETOF2DPOINTS_SETNAMENODE_H
