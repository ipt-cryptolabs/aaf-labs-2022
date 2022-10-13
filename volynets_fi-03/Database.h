#ifndef _DATABASE_
#define _DATABASE_
#include <iostream>
#include <string>
#include <vector>

class Database;
class Table;


class Database{
public:
    Database();
    Database createTable(std::string table_name,
        std::vector<std::string> columns,
        std::vector<std::string> indexed_columns);
    Database insert(std::string table_name,
        std::vector<std::string> values);
    Database select(std::string table_name,
        std::string condition,
        std::string order_column,
        std::string order_type);
};

class Table{
public:
    Table();
    Table insert();
    std::string select();
};

#include "Database.cpp"
#endif