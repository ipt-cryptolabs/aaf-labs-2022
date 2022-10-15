#pragma once
#include <tuple>
#include <string>

typedef std::pair<std::string, bool> query_result;

/**
 * Node structures that syntax tree is made of.
 * Defines connection between DataBase and Parser classes.
 */
class Node
{
    virtual query_result exec() = 0;
};

class NodeJOIN : public Node
{
    query_result exec() override;
};

class NodeSELECT : public  Node
{
    query_result exec() override;   
};

class NodeINSERT : public  Node
{
    query_result exec() override;
};

class NodeLITERAL : public  Node
{
    query_result exec() override;
};

class NodeCREATE : public  Node
{
    query_result exec() override;
};