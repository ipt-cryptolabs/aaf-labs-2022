#ifndef _DATABASE_
#define _DATABASE_
#include <iostream>
#include <string>

class Database;
class Table;


class Database{
public:
    Database();
    Database createTable();
    Database insert();
    Database select();
};

class Table{
public:
    Table();
    Table insert();
    std::string select();
};

#include "Database.cpp"
#endif