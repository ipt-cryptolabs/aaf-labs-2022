#ifndef SETOF2DPOINTS_RTREE_H
#define SETOF2DPOINTS_RTREE_H

#include <iostream>
#include <vector>
#include "Point.h"
#include "Rectangle.h"

class RTree {
    // RTree class represents storage for spacial data, namely 2D points(in this case)
    // Node is either INode or Leaf, m - min children nodes amount in node, M - max.
public:
    RTree(): root_(nullptr) {

    }

    void Insert(Point* point);
    void Print();
    bool Contains(Point* point);
    std::vector<Point*> Search();
    std::vector<Point*> SearchInside(Point* point1, Point* point2);
    std::vector<Point*> SearchNN(Point* point);
    std::vector<Point*> SearchLeftOf(int number);

private:
    class Node{
    public:
        virtual void polimorph() {  }
        Rectangle* rect_;
    };

    class Leaf: public Node{
    public:
        Leaf(Rectangle* rect, std::vector<Point*> points): points_(std::move(points)){
            rect_ = rect;
        }
        std::vector<Point*> points_;
    };

    class INode: public Node{
    public:
        INode(Rectangle* rect, std::vector<Node*> nodes): nodes_(std::move(nodes)){
            rect_ = rect;
        }
        std::vector<Node*> nodes_;
    };

    int const M = 3;
    int const m = 2;

    Node* root_;

    void SubPrint(Node* node, const std::string& shift, bool last);
    void SubPrint(Point* point, const std::string& shift, bool last);
    bool SubContains(Point* point, Node* node);
    void SubSearch(Node* node, std::vector<Point*>& collected_points);
    bool IsPointIn(Point* point, const std::vector<Point*>& points);
};


#endif //SETOF2DPOINTS_RTREE_H
