#include "Node.hpp"
#include "..\\DataBase\\DataBase.hpp"

query_result NodeJOIN::exec()
{
    // return DataBase::create_join(nullptr, nullptr,  "");
}

query_result NodeSELECT::exec()
{
    // return DataBase::select_from(nullptr, "");
}
    
query_result NodeINSERT::exec()
{
    // return DataBase::insert(nullptr, "");
}

query_result NodeLITERAL::exec()
{
    // return "";
}
