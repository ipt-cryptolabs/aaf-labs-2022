#pragma once
#include <tuple>
#include <string>
#include <vector>

// Predeclarations
enum class Result_Code : uint8_t;

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
        virtual query_result exec(DataBase*) = 0;
    };

    struct NodeJOIN : public Node
    {
        std::string table1, table2;
        std::string on_columns_condition;

        query_result exec(DataBase*) override;
    };

    struct NodeSELECT : public  Node
    {
        std::string from_table;
        std::string condition;

        query_result exec(DataBase*) override;   
    };

    struct NodeINSERT : public  Node
    {
        std::string table;
        std::vector<std::string> row;

        query_result exec(DataBase*) override;
    };

    struct NodeLITERAL : public  Node
    {
        std::string value;

        query_result exec(DataBase*) override;
    };

    struct NodeCREATE : public  Node
    {
        std::vector<std::pair<std::string, bool>> columns;

        query_result exec(DataBase*) override;
    };
}