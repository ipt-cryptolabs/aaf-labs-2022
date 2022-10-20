#include "commands.hpp"

bool CheckVarName(std::string name)
{
    return isalpha(name[0]);
}

bool CheckNum(std::string num)
{
    bool ret;
    for(auto i: num)
        ret = ret & isalnum(i);
    return ret;
}

Command::Command(){};
Command::~Command(){};
void Command::Execute(ExecManager &em){std::cout << "Placeholder for command" << std::endl;};

Exit::Exit(){};
Exit::~Exit(){};
void Exit::Execute(ExecManager &em){std::cout << "Placeholder for command exit" << std::endl;};

Create::Create(std::string name_): name(name_) {};
Create::~Create(){};
void Create::Execute(ExecManager &em){std::cout << "Placeholder for command create" << std::endl;};

Insert::Insert(std::string name_, std::int64_t x_, std::int64_t y_): name(name_), x(x_), y(y_) {};
Insert::~Insert(){};
void Insert::Execute(ExecManager &em){std::cout << "Placeholder for command insert" << std::endl;};

PrintTree::PrintTree(std::string name_): name(name_) {};
PrintTree::~PrintTree(){};
void PrintTree::Execute(ExecManager &em){std::cout << "Placeholder for command PrintTree" << std::endl;};

Contains::Contains(std::string name_, std::int64_t x_, std::int64_t y_): name(name_), x(x_), y(y_) {};
Contains::~Contains(){};
void Contains::Execute(ExecManager &em){std::cout << "Placeholder for command Contains" << std::endl;};

std::shared_ptr<Command> RecognizeComm(std::vector<std::string> tokens)
{

    if( tokens.size() == 0)
        throw std::invalid_argument("no command");
    if( tokens[0] == "CREATE")
    {
        if( !(tokens.size() == 2))
            throw std::invalid_argument("invalid count of arguments");
        if( !CheckVarName(tokens[1]))
            throw std::invalid_argument("invalid var name");
        return std::make_shared<Create>(tokens[1]);
    }

    //INSERT set_name (x, y);
    else if( tokens[0] == "INSERT")
    {
        if( !(tokens.size() == 7))
            throw std::invalid_argument("invalid count of arguments");
        if( !CheckVarName(tokens[1]))
            throw std::invalid_argument("invalid var name");
        if ( !(tokens[2] == "(" & tokens[4] == "," & tokens[6] == ")"))
            throw std::invalid_argument("invalid syntax");
        try
        {
            return std::make_shared<Insert>(tokens[1] ,stoi(tokens[3]), stoi(tokens[5]));
        }
        catch (std::exception& exc)
        {
            throw std::invalid_argument("invalid numbers");
        }
    }
    else if (tokens[0] == "PRINT_TREE")
    {
        if( !(tokens.size() == 2))
            throw std::invalid_argument("invalid count of arguments");
        if( !CheckVarName(tokens[1]))
            throw std::invalid_argument("invalid var name");
        return std::make_shared<PrintTree>(tokens[1]);
    }
    else if( tokens[0] == "CONTAINS")
    {
        if( !(tokens.size() == 7))
            throw std::invalid_argument("invalid count of arguments");
        if( !CheckVarName(tokens[1]))
            throw std::invalid_argument("invalid var name");
        if ( !(tokens[2] == "(" & tokens[4] == "," & tokens[6] == ")"))
            throw std::invalid_argument("invalid syntax");
        try
        {
            return std::make_shared<Contains>(tokens[1] ,stoi(tokens[3]), stoi(tokens[5]));
        }
        catch (std::exception& exc)
        {
            throw std::invalid_argument("invalid numbers");
        }
    }
    throw std::invalid_argument("unexpected command");
}