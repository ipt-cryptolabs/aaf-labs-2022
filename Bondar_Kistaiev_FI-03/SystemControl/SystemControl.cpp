#include "SystemControl.hpp"
#include "..\\Parser\\Parser.hpp"
#include "..\\DataBase\\DataBase.hpp"

// Temporary libs
#include <iostream>
#include <string>
#include <limits>


int SystemControl::init()
{
    std::string input_handler;
    DBCommand::Node* executable;
    while (true)
    {
        input_handler = get_input();

        // TODO: exit command
        executable = Parser::parse_command(input_handler);
        execute_input(executable);
    }
    
    return 0;   // No error while execution
}

std::string SystemControl::get_input()
{
    std::cout << "> ";
    // Read input
    std::string input;
    std::getline(std::cin, input, ';');
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');

    return input;
}

int SystemControl::execute_input(DBCommand::Node* cmd)
{
    // TODO : ADD EXCEPTION HANDLING
    cmd->exec(this->controlled_db);
    return 0;
}
