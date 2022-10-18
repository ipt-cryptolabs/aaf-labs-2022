#include "DataBase.hpp"

query_result DataBase::select_from(const std::string& tbl, const std::string& cond)
{
    return {"SELECT CALLED ON TABLE:  " + tbl + "  with condition:  " + cond, Result_Code::TextMessage};
}

query_result DataBase::create_join(const std::string& t1,  const std::string& t2, const std::string& on_col1, const std::string& on_col2)
{
    return {"JOIN RESULT: " + t1 + " x " + t2 + " ON " + on_col1 + " = " + on_col1, Result_Code::Table};
}

query_result DataBase::insert(const std::string& tbl, const std::vector<std::string>& row)
{
    std::string temp = "(";
    for (auto s : row)
        temp += (s + ", ");
        
    temp += ")";

    return {"INSERT CALLED ON TABLE:  " + tbl + "  with values:  " + temp, Result_Code::TextMessage};
}

query_result DataBase::create(const std::string& tbl_name, const std::vector<std::pair<std::string, bool>>& columns)
{
    return {"CREATED TABLE:  " + tbl_name, Result_Code::TextMessage};
}
                
query_result DataBase::get_table_string(const std::string& name) const
{
    return {"GET_TABLE CALLED", Result_Code::TextMessage};
}
