#include "DataBase.hpp"

query_result DataBase::select_from(const std::string& tbl, std::string greater_cond, std::string less_cond)
{
    return {"SELECT CALLED ON TABLE:  " + tbl + "\nWith condition:  " + greater_cond + " > " + less_cond, Result_Code::TextMessage};
}

query_result DataBase::create_join(const std::string& t1,  const std::string& t2, const std::string& on_col1, const std::string& on_col2)
{
    return {"JOIN RESULT: " + t1 + " x " + t2 + " ON " + on_col1 + " = " + on_col2, Result_Code::Table};
}

query_result DataBase::insert(const std::string& tbl, const std::vector<std::string>& row)
{
    std::string temp = "(";
    for (auto s : row)
        temp += (s + ", "); 
    temp.pop_back();
    temp[temp.size() - 1] = ')';

    return {"INSERT CALLED ON TABLE:  " + tbl + "\nWith values:  " + temp, Result_Code::TextMessage};
}

query_result DataBase::create(const std::string& tbl_name, const std::vector<std::pair<std::string, bool>>& columns)
{
    std::string temp = "(";
    for (auto [col, ind] : columns)
    {
        temp += col;
        if(ind)
            temp += " (indexed)";
        temp += ", ";
    }
    temp.pop_back();
    temp[temp.size() - 1] = ')';

    return {"CREATED TABLE:  " + tbl_name + "\nWith columns: " + temp, Result_Code::TextMessage};
}
                
query_result DataBase::get_table_string(const std::string& name) const
{
    return {"GET_TABLE CALLED", Result_Code::TextMessage};
}
