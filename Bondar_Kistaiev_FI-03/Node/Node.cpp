#include "Node.hpp"
#include "..\\DataBase\\DataBase.hpp"

query_result DBCommand::NodeJOIN::exec(DataBase* db)
{
    auto [res1, code1] = table1->exec(db);
    auto [res2, code2] = table2->exec(db);

    if(code1 == Result_Code::Table && code2 == Result_Code::Table)
        return db->create_join(res1, res2, on_column1, on_column2);
    else if(code1 != Result_Code::Table)
        return {res1, code1};
    else
        return {res2, code2};
}

query_result DBCommand::NodeSELECT::exec(DataBase* db)
{
    auto [res, code] = from_table->exec(db);

    if(code == Result_Code::Table)
        return db->select_from(res, condition);
    else
        return {res, code};
        
}
    
query_result DBCommand::NodeINSERT::exec(DataBase* db)
{
    return db->insert(table, row);
}

query_result DBCommand::NodeLITERAL::exec(DataBase* db)
{
    return {value, Result_Code::Table};
}

query_result DBCommand::NodeCREATE::exec(DataBase* db)
{
    return db->create(table_name, columns);
}