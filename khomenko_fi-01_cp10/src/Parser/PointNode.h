#ifndef SETOF2DPOINTS_POINTNODE_H
#define SETOF2DPOINTS_POINTNODE_H

#include "..//DB/RTree/Point.h"

class PointNode: public ASTNode {
public:
    PointNode(Token* point){
        std::string str = point->get_value();
        size_t idx = str.find(',');
        int x = std::atoi(str.substr(0, idx).c_str());
        int y = std::atoi(str.substr(idx + 1, str.size() - idx).c_str());

        value_ = new Point(x, y);
    }

    Point* get_value(){
        return value_;
    }

private:
    Point* value_;
};


#endif //SETOF2DPOINTS_POINTNODE_H
