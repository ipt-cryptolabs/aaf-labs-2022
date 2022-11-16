#ifndef SETOF2DPOINTS_RECTANGLE_H
#define SETOF2DPOINTS_RECTANGLE_H

#include "Point.h"

class Rectangle {
public:
    Rectangle(Point* lb_point, Point* rt_point): rt_point_(rt_point), lb_point_(lb_point) {

    }

    std::string ToString() {
        return {"[" + rt_point_->ToString() + ", " + "(" + rt_point_->ToString() + "]"};
    }

    int Square() const{
        return (rt_point_->x - lb_point_->x) * (rt_point_->y - lb_point_->y);
    }

    Point* get_lb_point(){
        return lb_point_;
    }

    Point* get_rt_point(){
        return rt_point_;
    }

private:
    // lb - left bottom
    // rt - right top

    Point* lb_point_;
    Point* rt_point_;
};


#endif //SETOF2DPOINTS_RECTANGLE_H
