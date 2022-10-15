#pragma once
#include <string>

/**
 * System Control Class that operates over
 * one separate Data Base
 */
class SystemControl
{
public:
    // Public interface to set-up and start DB
    int init();

private:
    std::string wait_for_input();
    int execute_input(std::string);
};