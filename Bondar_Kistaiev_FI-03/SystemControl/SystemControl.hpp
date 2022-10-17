#pragma once
#include <string>

// Predeclarations
class DataBase;
namespace DBCommand
{
    struct Node;
}

/**
 * System Control Class that operates over
 * one separate Data Base
 */
class SystemControl
{
    // Pointer to a specific DB controlled by class object
    DataBase* controlled_db;
public:
    SystemControl();
    ~SystemControl();

    // Public interface to set-up and start DB
    int start();

private:
    // Waiting and pre-formating user input
    std::string get_input();

    // Command execution
    int execute_input(DBCommand::Node*);
};