#ifndef _DATABASE_
#define _DATABASE_
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Database;
class Table;


class Database{
public:
    Database();
    std::string createTable(std::string table_name,
                            std::vector<std::string> columns,
                            std::vector<std::string> indexed_columns);
    std::string insert(std::string table_name,
                       std::vector<std::string> values);
    std::string select(std::string table_name,
                       std::string l_value,
                       std::string condition,
                       std::string r_value,
                       std::map<std::string, std::string> order_column_and_type);
};

class Table{
public:
    Table();
    Table insert();
    std::string select();
};

#include "Database.cpp"
#endif