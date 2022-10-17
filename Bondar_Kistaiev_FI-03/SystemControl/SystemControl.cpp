#include "SystemControl.hpp"
#include "..\\Parser\\Parser.hpp"
#include "..\\DataBase\\DataBase.hpp"

// Temporary libs
#include <iostream>
#include <string>
#include <limits>

SystemControl::SystemControl()
{
    controlled_db = new DataBase;
}

SystemControl::~SystemControl()
{
    if(controlled_db)
        delete controlled_db;
}

int SystemControl::start()
{
    std::string input_handler;
    while (true)
    {
        input_handler = get_input();

        // TODO: exit command
        DBCommand::Node* executable = Parser::parse_command(input_handler);
        auto [res, ret_code] = executable->exec(controlled_db);

        if(ret_code == Result_Code::Table)
        {
            auto [tbl, exists] = controlled_db->get_table_string(res);
            if (exists)
                std::cout << tbl << std::endl;
            else
                std::cout << "Table " + res + " does not exist.";
        }
        else
            std::cout << "Error: " + res << std::endl;
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
