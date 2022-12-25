#ifndef SETOF2DPOINTS_RECTANGLE_H
#define SETOF2DPOINTS_RECTANGLE_H

#include <cmath>
#include <algorithm>
#include "Point.h"

class Rectangle {
public:
    Rectangle(): lb_point_(Point(0, 0)), rt_point_(Point(0, 0)){

    }

    Rectangle(const Point& lb_point, const Point& rt_point): rt_point_(rt_point), lb_point_(lb_point) {

    }

    Rectangle(int left_bottom_x, int left_bottom_y, int right_top_x, int right_top_y) {
        lb_point_ = Point(left_bottom_x, left_bottom_y);
        rt_point_ = Point(right_top_x, right_top_y);
    }

    std::string ToString() {
        return {"[" + lb_point_.ToString() + ", " + rt_point_.ToString() + "]"};
    }

    int Square() const{
        return (rt_point_.x - lb_point_.x) * (rt_point_.y - lb_point_.y);
    }

    Point get_lb_point(){
        return lb_point_;
    }

    Point get_rt_point(){
        return rt_point_;
    }

    bool Contains(Point* point){
        return (lb_point_.x <= point->x) && (point->x <= rt_point_.x) && (lb_point_.y <= point->y) && (point->y<= rt_point_.y);
    }

    bool Intersects(Rectangle* rectangle){
        int min_x1 = lb_point_.x;
        int max_x1 = rt_point_.x;
        int min_y1 = lb_point_.y;
        int max_y1 = rt_point_.y;

        int min_x2 = rectangle->lb_point_.x;
        int max_x2 = rectangle->rt_point_.x;
        int min_y2 = rectangle->lb_point_.y;
        int max_y2 = rectangle->rt_point_.y;

        return (min_x2 <= max_x1) && (max_x2 >= min_x1) && (min_y2 <= max_y1) && (max_y2 >= min_y1);

    }

    Rectangle UpdatedRectangle(Point* point){
        // find new rectangle which includes point

        Point new_lb_point = lb_point_;
        Point new_rt_point = rt_point_;

        if(point->x < lb_point_.x){
            new_lb_point.x = point->x;
        }

        if(point->x > rt_point_.x){
            new_rt_point.x = point->x;
        }

        if(point->y < lb_point_.y){
            new_lb_point.y = point->y;
        }

        if(point->y > rt_point_.y){
            new_rt_point.y = point->y;
        }

        return {new_lb_point, new_rt_point};
    }

    Rectangle UpdatedRectangle(Rectangle* other_rectangle){
        // find new rectangle which includes this rectangle and other_rectangle

        Rectangle rect1 = UpdatedRectangle(&other_rectangle->lb_point_);
        Rectangle rect2 = rect1.UpdatedRectangle(&other_rectangle->rt_point_);

        return rect2;
    }

    int DistanceBetween(Point* point){
        Point center((lb_point_.x + rt_point_.x) / 2, (lb_point_.y + rt_point_.y) / 2);
        return Point::SqrDistance(&center, point);
    }

    int DistanceBetween(Rectangle* rectangle){
        Point center((lb_point_.x + rt_point_.x) / 2, (lb_point_.y + rt_point_.y) / 2);
        Point other_center((rectangle->lb_point_.x + rectangle->rt_point_.x) / 2,
                           (rectangle->lb_point_.y + rectangle->rt_point_.y) / 2);

        return Point::SqrDistance(&center, &other_center);
    }

private:
    // lb - left bottom
    // rt - right top

    Point lb_point_;
    Point rt_point_;
};


#endif //SETOF2DPOINTS_RECTANGLE_H
