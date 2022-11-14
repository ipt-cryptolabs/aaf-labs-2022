#ifndef SETOF2DPOINTS_DBIMPL_H
#define SETOF2DPOINTS_DBIMPL_H

#include <iostream>
#include "DatabaseDAO.h"

class DBImpl: public DatabaseDAO {
public:
    void Create(std::string set_name) override;
    void Insert(std::string set_name, std::pair<int, int> point) override;
    void Print(std::string set_name) override;
    void Contains(std::string set_name, std::pair<int, int> point) override;
    void Search(std::string set_name) override;
    void SearchInside(std::string set_name, std::pair<int, int> point1, std::pair<int, int> point2) override;
    void SearchNN(std::string set_name, std::pair<int, int> point) override;
    void SearchLeftOf(std::string set_name, int number) override;
};


#endif //SETOF2DPOINTS_DBIMPL_H
