#include "Database.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Database ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Database::Database(){
    tables = new std::map<std::string, Table>;
}

std::string Database::createTable(std::string table_name,
                                  std::vector<std::string> columns,
                                  std::vector<std::string> indexed_columns){
    if (tables->find(table_name) != tables->end()) {
        return "ERROR: table with name: " + table_name + " is exist.";
    }

    tables->insert({table_name, Table(columns, indexed_columns)});

    return "Table " + table_name + " created successfully.";
}

std::string Database::insert(std::string table_name, std::vector<std::string> values){
    if (tables->find(table_name) == tables->end()) {
        return "ERROR: table with name: " + table_name + " is not found.";
    }
    
    return tables->at(table_name).insert(values);
}

std::string Database::select(std::string table_name,
                   std::string l_value,
                   std::string condition,
                   std::string r_value,
                   std::vector<std::pair<std::string, std::string>> order_column_and_type){
    if (tables->find(table_name) == tables->end()) {
        return "ERROR: table with name: " + table_name + " is not found.";
    }

    if(l_value == "" && condition == "" && r_value == "" && order_column_and_type.size() == 0){
        return tables->at(table_name).select();
    }

    if(l_value == "" && condition == "" && r_value == "" && order_column_and_type.size() != 0){
        return tables->at(table_name).select(order_column_and_type);
    }

    if(l_value != "" && condition != "" && r_value != "" && order_column_and_type.size() == 0){
        return tables->at(table_name).select(l_value, condition, r_value);
    }
    
    return tables->at(table_name).select(l_value, condition, r_value, order_column_and_type);
}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////// less_than_key //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// class for sort algorithm

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

    for(auto i: indexed_columns){
        if(getIndex(columns, i) == -1){
            throw "undefinded index column name";
        }
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
    // select command start:
    if(getIndex(columns, l_value) == -1){
        return "undefinded left value of condition:" + l_value;
    }

    if(!is_condition(condition)){
        return "undefinded condition:" + condition;
    }

    if(r_value.at(0) != '"' && r_value.at(r_value.size()-1) != '"'){
        if(getIndex(columns, l_value) == -1){
            return "undefinded right value of condition:" + r_value;
        }
    }

    for(auto par: order_column_and_type){
        if(getIndex(columns, par.first) == -1){
            return "undefinded order element:" + par.first;
        }

        if(par.second!= "ASC" && par.second!= "DESC"){
            return "undefinded order type:" + par.second;
        }
    }

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

std::string Table::select(std::string l_value,
                       std::string condition,
                       std::string r_value){
    return select(l_value, condition, r_value, {});
}

std::string Table::select(std::vector<std::pair<std::string, std::string>> order_column_and_type){
    std::vector<std::vector<std::string>> temp_table(table);
    less_than_key ltk(columns, order_column_and_type);
    std::sort(temp_table.begin(), temp_table.end(), ltk);
    
    // print_tc(temp_table, columns);

    return str(temp_table);
}

std::string Table::select(){
    return str();
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
    for(int i = 0; i < t.size(); ++i){
        textable.setRow(i+1, t.at(i));
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

bool is_condition(std::string cond){
    bool is_a_condition = false;
    
    if(cond == ">")is_a_condition = true;
    if(cond == ">=")is_a_condition = true;
    if(cond == "==")is_a_condition = true;
    if(cond == "<=")is_a_condition = true;
    if(cond == "<")is_a_condition = true;
    if(cond == "<>")is_a_condition = true;

    return is_a_condition;
}



