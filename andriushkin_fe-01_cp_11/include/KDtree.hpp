#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stack>

class KDtree
{
public:
    class Node
    {   
    public:
        Node *left, *right;
        std::array<int64_t, 2> coords;
        bool rotation; // false -- x; true -- y
        Node(int64_t x, int64_t y, bool rot);
        void Print(std::vector<std::string> &prefix);
    };

    bool Insert(const int64_t &x_, const int64_t &y_);
    void PrintTree();
    std::vector<KDtree::Node*> GetAll();
    bool Contains(const int64_t &x_, const int64_t &y_);

private:
    Node *first_node;
};

std::ostream& operator<<(std::ostream& os, KDtree::Node node);

#endif