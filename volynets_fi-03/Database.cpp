#include "Database.h"

Database::Database(){}

std::string Database::createTable(std::string table_name,
                                  std::vector<std::string> columns,
                                  std::vector<std::string> indexed_columns){
    std::string answ = "Created table ";

    answ += table_name + "\nWith columns: ";

    for(int i = 0; i < columns.size(); ++i){
        answ += columns.at(i) + " ";
    }
    answ += "\nAnd with indexed columns: ";

    for(int i = 0; i < indexed_columns.size(); ++i){
        answ += indexed_columns.at(i) + " ";
    }
    answ += "\n";

    return answ;
}

std::string Database::insert(std::string table_name, std::vector<std::string> values){
    std::string answ = "Inserted in ";

    answ += table_name + "\nValues: ";

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
    std::string answ = "Selected in ";

    answ += table_name + "\nWhere: ";

    answ += l_value + " " + condition + " " + r_value + "\nOrdering by: ";

    for(auto elem: order_column_and_type){
        answ += elem.first + ":" + elem.second + " ";
    }
    answ += "\n";

    return answ;
}