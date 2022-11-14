#ifndef SETOF2DPOINTS_DB_H
#define SETOF2DPOINTS_DB_H

#include <iostream>
#include <unordered_map>
#include "RTree/RTree.h"
#include "../Exception.h"

class DB {
public:
    void Create(const std::string& set_name);
    void Insert(const std::string& set_name, std::pair<int, int> point);
    void Print(const std::string& set_name);
    void Contains(const std::string& set_name, std::pair<int, int> point);
    void Search(const std::string& set_name);
    void SearchInside(const std::string& set_name, std::pair<int, int> point1, std::pair<int, int> point2);
    void SearchNN(const std::string& set_name, std::pair<int, int> point);
    void SearchLeftOf(const std::string& set_name, int number);

private:
    std::unordered_map<std::string, RTree*> sets_;

    void CheckSetPresence(const std::string& set_name);
};


#endif //SETOF2DPOINTS_DB_H
