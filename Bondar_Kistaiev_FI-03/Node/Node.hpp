#pragma once
#include <tuple>
#include <string>

// Predeclarations
typedef std::pair<std::string, bool> query_result;
class DataBase;

/**
 * Node structures that syntax tree is made of.
 * Defines connection between DataBase and Parser classes.
 */
namespace DBCommand
{
    struct Node
    {
        virtual query_result exec(DataBase*) = 0;
    };

    struct NodeJOIN : public Node
    {
        query_result exec(DataBase*) override;
    };

    struct NodeSELECT : public  Node
    {
        query_result exec(DataBase*) override;   
    };

    struct NodeINSERT : public  Node
    {
        query_result exec(DataBase*) override;
    };

    struct NodeLITERAL : public  Node
    {
        query_result exec(DataBase*) override;
    };

    struct NodeCREATE : public  Node
    {
        query_result exec(DataBase*) override;
    };
}