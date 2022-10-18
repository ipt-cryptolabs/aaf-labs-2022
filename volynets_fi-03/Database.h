#ifndef _DATABASE_
#define _DATABASE_
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "textable-master/textable.h"
#include "textable-master/textable.cpp"

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
                       std::vector<std::pair<std::string, std::string>> order_column_and_type);

private:
    std::map<std::string, Table> *tables;
};

struct less_than_key{
    less_than_key(std::vector<std::string> columns,
                  std::vector<std::pair<std::string, std::string>> order_column_and_type);
    inline bool operator() (std::vector<std::string> row1,
                            std::vector<std::string> row2);

private:
    std::vector<std::string> columns;
    std::vector<std::pair<std::string, std::string>> order_column_and_type;
};

class Table{
public:
    Table(std::vector<std::string> columns,
          std::vector<std::string> indexed_columns = {});
    std::string insert(std::vector<std::string> values);
    std::string select(std::string l_value,
                       std::string condition,
                       std::string r_value,
                       std::vector<std::pair<std::string, std::string>> order_column_and_type);
    std::string select(std::string l_value,
                       std::string condition,
                       std::string r_value);
    std::string select(std::vector<std::pair<std::string, std::string>> order_column_and_type);
    std::string select();
    void print();
    int getSize();
    std::string str();

private:
    std::vector<std::vector<std::string>> table;
    std::vector<std::string> columns;
    std::vector<std::string> indexed_columns;
    std::string str(std::vector<std::vector<std::string>> t);
};

int getIndex(std::vector<std::string> v, std::string K);
void print_tc(std::vector<std::vector<std::string>> table, std::vector<std::string> columns);
bool compare(std::string s1, std::string s2, std::string comp_s);
bool is_condition(std::string cond);

#include "Database.cpp"
#endif