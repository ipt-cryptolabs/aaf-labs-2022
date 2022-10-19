#pragma once

// Headers to use
#include <string>

// Utility types and predeclarations
class DataBase;
namespace DBCommand
{
    struct Node;
}

/**
 * System Control Class that provides
 * control over separate Data Base
 * and user interface.
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
};
