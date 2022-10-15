#pragma once

#include "..\\DataBase\\DataBase.hpp"

/**
 * Node structures that syntax tree is made of.
 * Defines connection between DataBase and Parser classes.
 */
class Node
{
    virtual DataBase::Table* exec() = 0;
};

class NodeJOIN : Node
{
    DataBase::Table* exec() override;
};

class NodeSELECT : Node
{
    DataBase::Table* exec() override;   
};

class NodeINSERT : Node
{
    DataBase::Table* exec() override;
};

class NodeLITERAL : Node
{
    std::string exec() override;
};

class NodeCREATE : Node
{
    DataBase::Table* exec() override;
};