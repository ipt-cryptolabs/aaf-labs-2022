#include "Node.hpp"
#include "..\\DataBase\\DataBase.hpp"

query_result DBCommand::NodeJOIN::exec(DataBase* db)
{
    return db->create_join(table1, table2,  on_columns_condition);
}

query_result DBCommand::NodeSELECT::exec(DataBase* db)
{
    return db->select_from(from_table, condition);
}
    
query_result DBCommand::NodeINSERT::exec(DataBase* db)
{
    return db->insert(table, row);
}

query_result DBCommand::NodeLITERAL::exec(DataBase* db)
{
    return {value, Result_Code::Value};
}

query_result DBCommand::NodeCREATE::exec(DataBase* db)
{
    return db->create(columns);
}