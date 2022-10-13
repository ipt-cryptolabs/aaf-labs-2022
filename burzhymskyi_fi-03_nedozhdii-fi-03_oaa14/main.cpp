#include <iostream>
#include "Tree.h"


int main() {

    std::stringstream buffer;
    //std::cout<<buffer.eof()<< ' ';
   // buffer<<"00";   std::cout<<buffer.str()<<' ';
    //std::cout<< ;
    Tree a;
    std::string b = "fmc";
   // std::cout<<b.substr(0,2);

    a.insert("abc");//todo check in when two letters in a row
    a.insert("a");
    a.insert("abf");
    a.insert("fm");
    a.insert("bc");
    a.insert("fmc");
    a.insert("fml");
    a.insert("fmlc");
    a.insert("fmlk");
    a.insert("fmlkncd");
    a.insert("fmlknfd");
    a.insert("ghj");
//    std::cout<<a.search(nullptr,0, nullptr,"");


    a.printTree( "","", nullptr,0, false);
    return 0;
}
