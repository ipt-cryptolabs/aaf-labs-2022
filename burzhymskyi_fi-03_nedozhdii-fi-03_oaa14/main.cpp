#include <iostream>
#include "Tree.h"


int main() {


    Tree a;
    std::string b = "fmc";

    a.insert("abc");//todo check in when two letters in a row
    a.insert("a");
    a.insert("abc");
    a.insert("fm");
    a.insert("bc");
    a.insert("fmc");
    a.insert("fml");
    a.insert("fmlc");
    a.insert("fmlk");
    a.insert("fmlkncd");
    a.insert("fmlknfd");
    a.insert("ghj");
    a.printTree();
    a.insert("gmj");
//    std::cout<<a.search(nullptr,0, nullptr,"");
    a.printTree();
    

    return 0;
}
