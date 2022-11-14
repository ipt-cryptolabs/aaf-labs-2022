#ifndef SETOF2DPOINTS_POINTNODE_H
#define SETOF2DPOINTS_POINTNODE_H


class PointNode: public ASTNode {
public:
    PointNode(Token* point){
        std::string str = point->get_value();
        size_t idx = str.find(',');
        int x = std::atoi(str.substr(0, idx).c_str());
        int y = std::atoi(str.substr(idx + 1, str.size() - idx).c_str());
        value_ = std::make_pair(x, y);
    }

    std::pair<int, int> get_value(){
        return value_;
    }

private:
    std::pair<int, int> value_;
};


#endif //SETOF2DPOINTS_POINTNODE_H
