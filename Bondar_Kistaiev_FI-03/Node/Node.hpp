#pragma once
#include <tuple>
#include <string>

// Predeclarations
enum class Result_Code : uint8_t { Error = 0, Table = 1, TextMssg = 2 };

typedef std::pair<std::string, Result_Code> query_result;
class DataBase;

/**
 * Node structures that syntax tree is made of.
 * Defines connection between DataBase and Parser classes.
 */
namespace DBCommand
{
    struct Node
    {
        std::string value;
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