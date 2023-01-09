#pragma once

// Headers to use
#include <string>
#include <vector>

// Utility types and predeclarations
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
        virtual ~Node() = default;
    };

    struct NodeJOIN : public Node
    {
        Node *table1, *table2;
        std::string on_column1, on_column2;

        ~NodeJOIN();
        query_result exec(DataBase*) override;
    };

    struct NodeSELECT : public Node
    {
        Node* from_table;
        std::string g_cond, l_cond;

        ~NodeSELECT();
        query_result exec(DataBase*) override;   
    };

    struct NodeINSERT : public Node
    {
        std::string table;
        std::vector<std::string> row; 

        ~NodeINSERT() = default;
        query_result exec(DataBase*) override;
    };

    struct NodeVALUE : public Node
    {
        std::string value;
        Result_Code type;

        ~NodeVALUE() = default;
        query_result exec(DataBase*) override;
    };

    struct NodeCREATE : public Node
    {
        std::string table_name;
        std::vector<std::pair<std::string, bool>> columns; // std::std::std::standart moment

        ~NodeCREATE() = default;
        query_result exec(DataBase*) override;
    };
}
