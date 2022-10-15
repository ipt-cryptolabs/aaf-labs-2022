#include "Node.hpp"

 DataBase::Table* NodeJOIN::exec()
 {
    return DataBase::create_join(nullptr, nullptr,  "");
 }

DataBase::Table* NodeSELECT::exec()
 {
    return DataBase::select_from(nullptr, "");
 }
    
DataBase::Table* NodeINSERT::exec()
{
    return DataBase::insert(nullptr, "");
}

std::string NodeLITERAL::exec()
{
    return "";
}
