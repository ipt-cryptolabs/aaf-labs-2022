#ifndef BURZHYMSKYI_FI_03_NEDOZHDII_FI_03_OAA14_TREE_H
#define BURZHYMSKYI_FI_03_NEDOZHDII_FI_03_OAA14_TREE_H

#include <iostream>
#include <string>
#include <sstream>
#define sizeAlphabet = 256;

class Tree
{
public:
    class Node
    {
    public:
        char *letter = nullptr;

        bool endWord;//show that some of substring is string;
        int countChildrens = 0;
        Node *childrens[95];
        Node();
        Node(const char&);
        void print( std::string prefix, std::string childrenPrefix);
        ~Node();
    };

    Tree(const std::string);
    Tree();
    ~Tree();

    void insert(std::string);
    bool contains(std::string);

    void search();
    void printTree();
    Node *root;
private:
    void searchTree(Node* cur, std::string&);

};


#endif //BURZHYMSKYI_FI_03_NEDOZHDII_FI_03_OAA14_TREE_H
