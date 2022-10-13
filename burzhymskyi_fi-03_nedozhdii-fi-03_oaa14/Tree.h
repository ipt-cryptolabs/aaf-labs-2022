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
        bool exist[94];//symbols from ! to ~ in ASCII, ! =33
        char *letter;
        bool endBranch;
        bool endWord;//show that some of substring is string;
        int countChildrens = 0;
        Node *childrens[94];
        Node();
        Node(const char&, const bool&);
        ~Node();
    };

    Tree(const std::string);
    Tree();
    ~Tree();

    void insert(std::string);
    bool contains(std::string);
    std::string search(Node* cur, int ,std::string*, std::string);
    void printTree( std::string prefix, std::string childrenPrefix,Node*,int,bool);
    Node *root;
private:


};


#endif //BURZHYMSKYI_FI_03_NEDOZHDII_FI_03_OAA14_TREE_H
