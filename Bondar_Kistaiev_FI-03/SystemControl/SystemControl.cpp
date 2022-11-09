#include "SystemControl.hpp"
#include "../Parser/Parser.hpp"
#include "../DataBase/DataBase.hpp"
#include "../Node/Node.hpp"

// Temporary libs
#include <iostream>
#include <limits>
#include <algorithm>

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
    std::string word;

    while (true)
    {
        input_handler = get_input();

        word = input_handler;
        std::transform(word.begin(), word.end(), word.begin(), [](char c) { return std::tolower(c); });

        if (word == "exit;" || word == "quit;")
            return 1;

        DBCommand::Node* executable = Parser::parse_command(input_handler);
        auto [res, ret_code] = executable->exec(this->controlled_db);

        switch (ret_code)
        {
            case Result_Code::Table :
            {
                auto [tbl, exists] = this->controlled_db->get_table_string(res);

                if (exists == Result_Code::Table)
                    std::cout << tbl << std::endl;
                else if (exists == Result_Code::Error)
                    std::cout << "Table " + res + " does not exist.";
                else 
                    std::cout << "HOW TF DID YOU GET HERE???";

                break;
            }
            case Result_Code::Error :
            {
                std::cout << std::endl << "Error:   " + res << std::endl;
                break;
            }
            default:
            {
                std::cout << std::endl << res << std::endl;
                break;
            }
        }
        
        std::cout << std::endl;
        delete executable;
    }
}

std::string SystemControl::get_input()
{
    std::cout << "> ";
    // Read input
    std::string input;
    std::getline(std::cin, input, ';');
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');

    return input + ";";
}
