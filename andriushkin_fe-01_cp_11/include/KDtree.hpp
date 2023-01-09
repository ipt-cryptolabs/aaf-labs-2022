#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stack>
#include <math.h>
#include <array>

class KDtree
{
public:
    class Node
    {   
    public:
        Node *left = nullptr, *right = nullptr;
        std::array<int64_t, 2> coords;
        bool rotation; // false -- x; true -- y
        Node(int64_t x, int64_t y, bool rot);
        void Print(std::vector<std::string> &prefix);

    };

    bool Insert(const int64_t &x_, const int64_t &y_);
    void PrintTree();
    std::vector<KDtree::Node*> GetAll();
    std::vector<KDtree::Node*> RangeSearch(int64_t x1, int64_t y1, int64_t x2, int64_t y2);
    bool Contains(const int64_t &x_, const int64_t &y_);
    std::vector<Node*> NNSearch(int64_t x, int64_t y);
    std::vector<Node*> AboveSearch(int64_t y);

private:
    Node *first_node;
};

struct bounding_box
{
    KDtree::Node* node;
    std::array<int64_t, 2> left_box, right_box;    
};

bool Intersection(std::array<int64_t,2> l1, std::array<int64_t,2> l2,
    std::array<int64_t,2> r1, std::array<int64_t,2> r2);
bool InRectange(std::array<int64_t,2> left, std::array<int64_t,2> right, std::array<int64_t,2> point);

double Distance(std::array<int64_t,2> left, std::array<int64_t,2> right);

double DistanceToBox(bounding_box box, std::array<int64_t,2> point);

std::ostream& operator<<(std::ostream& os, KDtree::Node node);

#endif