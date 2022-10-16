#include "Node.hpp"
#include "..\\DataBase\\DataBase.hpp"

query_result DBCommand::NodeJOIN::exec(DataBase*)
{
    // return DataBase::create_join(nullptr, nullptr,  "");
}

query_result DBCommand::NodeSELECT::exec(DataBase*)
{
    // return DataBase::select_from(nullptr, "");
}
    
query_result DBCommand::NodeINSERT::exec(DataBase*)
{
    // return DataBase::insert(nullptr, "");
}

query_result DBCommand::NodeLITERAL::exec(DataBase*)
{
    // return "";
}
