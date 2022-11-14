#ifndef SETOF2DPOINTS_RTREE_H
#define SETOF2DPOINTS_RTREE_H

#include <iostream>

class RTree {
public:
    void Insert(std::pair<int, int> point) {};
    void Print() {};
    void Contains(std::pair<int, int> point) {};
    void Search() {};
    void SearchInside(std::pair<int, int> point1, std::pair<int, int> point2) {};
    void SearchNN(std::pair<int, int> point) {};
    void SearchLeftOf(int number) {};
};


#endif //SETOF2DPOINTS_RTREE_H
