#ifndef SETOF2DPOINTS_POINT_H
#define SETOF2DPOINTS_POINT_H

#include <cmath>

class Point {
public:
    Point(): x(0), y(0){

    }

    Point(int x, int y): x(x), y(y){

    }

    Point(const Point& point): x(point.x), y(point.y){

    }

    std::string ToString(){
        return "(" + std::to_string(x) + ", " +  std::to_string(y) + ")";
    }

    int x;
    int y;
};


#endif //SETOF2DPOINTS_POINT_H
