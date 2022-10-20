#pragma once

#include <string>


class Node
{
private:
    Node *left, *right;
    uint64_t x, y;
public:
    Node();
    ~Node();
    void Insert(const uint64_t &num);
};

class KDtree
{
private:
    const std::string name;
    Node *first_node;
public:
    KDtree(std::string name_){};
    ~KDtree(){};
};
