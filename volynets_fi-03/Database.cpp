#include "Database.h"

Database::Database(){}

std::string Database::createTable(std::string table_name,
                                  std::vector<std::string> columns,
                                  std::vector<std::string> indexed_columns){
    std::string answ = "Create table ";

    answ += table_name + "\n";

    for(int i = 0; i < columns.size(); ++i){
        answ += columns.at(i) + " ";
    }
    answ += "\n";

    for(int i = 0; i < indexed_columns.size(); ++i){
        answ += indexed_columns.at(i) + " ";
    }
    answ += "\n";

    return answ;
}

std::string Database::insert(std::string table_name, std::vector<std::string> values){
    std::string answ = "insert ";

    answ += table_name + "\n";

    for(int i = 0; i < values.size(); ++i){
        answ += values.at(i) + " ";
    }
    answ += "\n";

    return answ;
}

std::string Database::select(std::string table_name,
                   std::string l_value,
                   std::string condition,
                   std::string r_value,
                   std::map<std::string, std::string> order_column_and_type){
    std::string answ = "select ";

    answ += table_name + "\n";

    answ += l_value + " " + condition + " " + r_value + "\n";

    for(auto elem: order_column_and_type){
        answ += elem.first + ":" + elem.second + " ";
    }
    answ += "\n";

    return answ;
}