#ifndef SETOF2DPOINTS_POINT_H
#define SETOF2DPOINTS_POINT_H


class Point {
public:
    Point(int x, int y): x(x), y(y){

    }

    std::string ToString(){
        return "(" + std::to_string(x) + ", " +  std::to_string(y) + ")";
    }

    int x;
    int y;
};


#endif //SETOF2DPOINTS_POINT_H
