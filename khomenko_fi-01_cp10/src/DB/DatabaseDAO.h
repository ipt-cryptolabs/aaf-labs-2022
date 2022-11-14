#ifndef SETOF2DPOINTS_DATABASEDAO_H
#define SETOF2DPOINTS_DATABASEDAO_H


#include <string>

class DatabaseDAO {
public:
    virtual void Create(std::string set_name) = 0;
    virtual void Insert(std::string set_name, std::pair<int, int> point) = 0;
    virtual void Print(std::string set_name) = 0;
    virtual void Contains(std::string set_name, std::pair<int, int> point) = 0;
    virtual void Search(std::string set_name) = 0;
    virtual void SearchInside(std::string set_name, std::pair<int, int> point1, std::pair<int, int> point2) = 0;
    virtual void SearchNN(std::string set_name, std::pair<int, int> point) = 0;
    virtual void SearchLeftOf(std::string set_name, int number) = 0;
};


#endif //SETOF2DPOINTS_DATABASEDAO_H
