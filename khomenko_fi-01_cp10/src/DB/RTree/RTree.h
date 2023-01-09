#ifndef SETOF2DPOINTS_RTREE_H
#define SETOF2DPOINTS_RTREE_H

#include <iostream>
#include <vector>
#include "Point.h"
#include "Rectangle.h"

class RTree {
    // RTree class represents storage for spacial data, namely 2D points(in this case)
    // Node is either INode or Leaf, m_ - min children nodes amount in node, M_ - max.
public:
    RTree(int m, int M): root_(nullptr) {
        m_ = m;
        M_ = M;
    }

    bool Insert(Point* point);
    void Print();
    bool Contains(Point* point);
    std::vector<Point*> Search();
    std::vector<Point*> SearchInside(Point* point1, Point* point2);
    std::vector<Point*> SearchNN(Point* point);
    std::vector<Point*> SearchLeftOf(int x);

private:
    class Node{
    public:
        virtual void polimorph() {  }
        Rectangle rect_;

        virtual void UpdateMBR() = 0;
    };

    class Leaf: public Node{
    public:
        Leaf() = default;

        void UpdateMBR() override{
            rect_ = Rectangle(*points_[0], *points_[0]);

            for(int i = 1; i < points_.size(); i++){
                rect_ = rect_.UpdatedRectangle(points_[i]);
            }
        }

        std::vector<Point*> points_;
    };

    class INode: public Node{
    public:
        INode() = default;

        void UpdateMBR() override{
            rect_ = Rectangle(nodes_[0]->rect_);

            for(int i = 1; i < nodes_.size(); i++){
                rect_ = rect_.UpdatedRectangle(&nodes_[i]->rect_);
            }
        }

        std::vector<Node*> nodes_;
    };

    int M_;
    int m_;

    Node* root_;


    static bool sort_func(const std::pair<Node*, int> &a, const std::pair<Node*, int> &b)
    {
        return (a.second > b.second);
    }

    void SubPrint(Node* node, const std::string& shift, bool last);
    void SubPrint(Point* point, const std::string& shift, bool last);
    bool SubContains(Point* point, Node* node);
    void SubSearch(Node* node, std::vector<Point*>& collected_points);
    void SubSearchLeftOf(Node* node, int x, std::vector<Point*>& collected_points);
    void SubSearchInside(Node* node, Rectangle* rectangle, std::vector<Point*>& collected_points);
    void SubSearchNN(Node* node, Point* point, std::vector<Point*>& collected_points, int &min_distance);
    Node* SubInsert(Point* point, Node* node);
    Node* ChooseSubtree(RTree::INode* node, Point* point);

    INode* QuadraticSplit(INode* inode);
    Leaf* QuadraticSplit(Leaf* leaf);

    void PickSeeds(Leaf* leaf, Leaf* split_leaf, std::vector<Point*>& points);
    void QDistribute(Leaf* leaf, Leaf* split_leaf, std::vector<Point*>& points);
    Point* PickNext(Leaf* leaf, Leaf* split_leaf, const std::vector<Point *>& points);

    void PickSeeds(INode* node, INode* split_node,  std::vector<Node*>& nodes);
    void QDistribute(INode* node, INode* split_node, std::vector<Node*>& nodes);
    Node* PickNext(Node* node, Node* split_node, const std::vector<Node*>& nodes);
};


#endif //SETOF2DPOINTS_RTREE_H
