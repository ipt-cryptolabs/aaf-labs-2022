#include "Database.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Database ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

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
                   std::vector<std::pair<std::string, std::string>> order_column_and_type){
    std::string answ = "Selected in ";

    answ += table_name + "\nWhere: ";

    answ += l_value + " " + condition + " " + r_value + "\nOrdering by: ";

    for(auto elem: order_column_and_type){
        answ += elem.first + ":" + elem.second + " ";
    }
    answ += "\n";

    return answ;
}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////// less_than_key //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

less_than_key::less_than_key(std::vector<std::string> columns,
                std::vector<std::pair<std::string, std::string>> order_column_and_type):
                columns(columns), order_column_and_type(order_column_and_type){
    //
}

inline bool less_than_key::operator() (std::vector<std::string> row1,
                                       std::vector<std::string> row2){
    for(auto comp: order_column_and_type){
        if(row1.at(getIndex(columns, comp.first)) != row2.at(getIndex(columns, comp.first))){
            if(comp.second == "ASC"){
                return (row1.at(getIndex(columns, comp.first)) < row2.at(getIndex(columns, comp.first)));
            }else if(comp.second == "DESC"){
                return (row1.at(getIndex(columns, comp.first)) > row2.at(getIndex(columns, comp.first)));
            }
        }
    }

    for(auto comp_coll: columns){
        if(row1.at(getIndex(columns, comp_coll)) != row2.at(getIndex(columns, comp_coll))){
            return (row1.at(getIndex(columns, comp_coll)) < row2.at(getIndex(columns, comp_coll)));
        }
    }

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Table //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Table::Table(std::vector<std::string> columns,
             std::vector<std::string> indexed_columns): columns(columns), indexed_columns(indexed_columns){
    if(columns.size() == 0){
        throw "ERROR, no columns had been written";
    }
}

std::string Table::insert(std::vector<std::string> values){
    if(columns.size() != values.size()){
        return "ERROR, insertion failed: number of values is incorect.";
    }

    std::vector<std::string> temp;
    for(int i = 0; i < values.size(); ++i){
        temp.push_back(values.at(i));
    }

    table.push_back(temp);

    return "New row has been added successfully";   
}

std::string Table::select(std::string l_value,
                          std::string condition,
                          std::string r_value,
                          std::vector<std::pair<std::string, std::string>> order_column_and_type){
    std::vector<std::vector<std::string>> temp_table;

    if(r_value.at(0) == '"' && r_value.at(r_value.size()-1) == '"'){
        r_value = r_value.substr(1, r_value.size()-2);
        for(auto row: table){
            int l_value_index = getIndex(columns, l_value);
            if(l_value_index == -1){
                throw "ERROR: bad left value of condition.";
            }

            if(compare(row.at(l_value_index), r_value, condition)){
                temp_table.push_back(row);
            }
        }
    }else{
        for(auto row: table){            
            if(compare(row.at(getIndex(columns, l_value)), row.at(getIndex(columns, r_value)), condition)){
                temp_table.push_back(row);
            }
        }
    }

    less_than_key ltk(columns, order_column_and_type);
    std::sort(temp_table.begin(), temp_table.end(), ltk);
    
    // print_tc(temp_table, columns);

    return str(temp_table);
}

void Table::print(){
    Textable textable;
    textable.setRow(0, columns);
    for(int i = 0; i < table.size(); ++i){
        textable.setRow(i+1, table.at(i));
    }

    std::cout << textable;
}

std::string Table::str(){
    return str(table);
}

std::string Table::str(std::vector<std::vector<std::string>> t){
    Textable textable;
    textable.setRow(0, columns);
    for(int i = 0; i < table.size(); ++i){
        textable.setRow(i+1, table.at(i));
    }

    std::stringstream ss;
    ss << textable;



    return ss.str();
}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////// Help functions /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int getIndex(std::vector<std::string> v, std::string K){
    auto it = find(v.begin(), v.end(), K);

    if (it != v.end()) {
        int index = it - v.begin();
        return index;
    }
    
    return -1;
}

void print_tc(std::vector<std::vector<std::string>> table, std::vector<std::string> columns){
    Textable textable;
    textable.setRow(0, columns);
    for(int i = 0; i < table.size(); ++i){
        textable.setRow(i+1, table.at(i));
    }

    std::cout << textable;
}

bool compare(std::string s1, std::string s2, std::string comp_s){
    if(comp_s == ">"){
        return (s1 > s2);
    }
    
    if(comp_s == ">="){
        return (s1 >= s2);
    }

    if(comp_s == "=="){
        return (s1 == s2);
    }

    if(comp_s == "<="){
        return (s1 <= s2);
    }

    if(comp_s == "<"){
        return (s1 < s2);
    }

    if(comp_s == "<>"){
        return (s1 != s2);
    }

    throw ("Compare string error when get" + comp_s);
    return 0;
}


